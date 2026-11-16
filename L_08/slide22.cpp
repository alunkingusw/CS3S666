// Build (Linux):    g++ main.cpp -lOpenCL

// Ask for the OpenCL 1.2 API. Slide 26 uses clCreateCommandQueue, which was
// deprecated in OpenCL 2.0; targeting 1.2 keeps it warning-free. Most devices will use 1.2
#define CL_TARGET_OPENCL_VERSION 120

#include <CL/cl.h>

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// ---------------------------------------------------------------------------
// Error checking (Slide 23)
// Wrap every OpenCL call so that failures are reported where they happen.
// Code 0 is CL_SUCCESS; anything else is a negative number from the table.
// ---------------------------------------------------------------------------
#define CHECK(err)                                                           \
    do {                                                                     \
        cl_int e_ = (err);                                                   \
        if (e_ != CL_SUCCESS) {                                              \
            cerr << "OpenCL error " << e_ << " at " << __FILE__ << ":"       \
                 << __LINE__ << "\n";                                        \
            exit(1);                                                         \
        }                                                                    \
    } while (0)

int main()
{
    cl_int err;   // reused for return codes throughout

   
    // Set up OpenCL
    // The "ask twice" pattern: first ask how many, then allocate, then ask
    // for the actual list. You will see this pattern again.

    // query the number of platforms
    cl_uint numPlatforms;
    err = clGetPlatformIDs(0, nullptr, &numPlatforms);
    CHECK(err);
    if (numPlatforms == 0) {
        cerr << "No OpenCL platforms found (is a driver installed?)\n";
        return 1;
    }

    // create the array of available platforms
    cl_platform_id* platformArray =
        (cl_platform_id*)malloc(numPlatforms * sizeof(cl_platform_id));

    // ask OpenCL for the available platform IDs
    err = clGetPlatformIDs(numPlatforms, platformArray, nullptr);
    CHECK(err);

    cout << "Found " << numPlatforms << " platform(s)\n";

    int platformIndex = 0;   // use the first available platform

    cl_context_properties contextProperties[] = {
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)platformArray[platformIndex],
        0
    };

    // Try to create a context around a GPU device so our kernels run on the GPU.
    cl_context context = clCreateContextFromType(
        contextProperties, CL_DEVICE_TYPE_GPU, nullptr, nullptr, &err);

    // if this machine has no GPU
    // on that platform fall back to
    // any device type so the demo still runs.
    if (err != CL_SUCCESS) {
        cout << "No GPU found on platform " << platformIndex
             << " (error " << err << "), falling back to any device\n";
        context = clCreateContextFromType(
            contextProperties, CL_DEVICE_TYPE_ALL, nullptr, nullptr, &err);
    }
    CHECK(err);

    //note the only bit of code we needed to change was the DEVICE flag.
    //this means we can try with the GPU preference, but fall back if
    //needed, without having to subsequently change the code.

    //Step 1: load in the HelloWorld file to a string
    ifstream kernelFile("HelloWorld.cl", ios::in);
    if (!kernelFile.is_open()) {
        cerr << "Cannot open HelloWorld.cl - run from the folder containing it\n";
        return 1;
    }

    // store the file contents in a stringstream object
    ostringstream oss;
    oss << kernelFile.rdbuf();

    // extract a std::string from the stringstream object
    string srcString = oss.str();

    // obtain a pointer to the contained C string
    const char* src = srcString.c_str();

    
    // Step 2: Create the program object from the source HelloWorld.cl
    // count = 1 string; lengths = NULL because the string is null-terminated.
    
    cl_program program;
    cl_int clerr;
    program = clCreateProgramWithSource(context, 1, (const char**)&src, 0, &clerr);
    CHECK(clerr);

    // Step 3: Build the program for the devices in the context
    // NULL device list = all devices in the context; NULL options = defaults.
    err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);


    // Running the code
    
    // 1) Create a command queue for the device (Slide 26)
    // The command queue is the ONLY way to talk to a device.
    // Again the "ask twice" pattern: get size, allocate, get data.
    
    size_t deviceBufferSize;
    clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, nullptr, &deviceBufferSize);
    cl_device_id* contextDevices = (cl_device_id*)malloc(deviceBufferSize);
    clGetContextInfo(context, CL_CONTEXT_DEVICES, deviceBufferSize, contextDevices, 0);
    cl_device_id device = contextDevices[0];

    // show which device we ended up on.
    char deviceName[256];
    clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(deviceName), deviceName, nullptr);
    cout << "Running on device: " << deviceName << "\n";

    // Create the command queue based on the device
    cl_command_queue commandQueue = clCreateCommandQueue(context, device, 0, &err);
    CHECK(err);

    
    // 2) Get a kernel object from the built program
    // The program is like a library; here we pick out one function by name.
    // A misspelt name gives error -46 (CL_INVALID_KERNEL_NAME).
    
    cl_kernel kernel = clCreateKernel(program, "hello_kernel", &err);
    CHECK(err);

    
    // 3) Set up the memory buffers

    // three arrays in ordinary host (C++) memory
    const int ARRAY_SIZE = 16;
    float host_a[ARRAY_SIZE];
    float host_b[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        host_a[i] = float(i);
        host_b[i] = float(i);
    }
    float host_result[ARRAY_SIZE];   // data will come back from OpenCL

    // matching buffers on the device. These are SEPARATE COPIES.
    // COPY_HOST_PTR copies the host data into the buffer when it is created.
    cl_mem buffer_a = clCreateBuffer(context,
        CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        ARRAY_SIZE * sizeof(float), host_a, &err);
    CHECK(err);

    cl_mem buffer_b = clCreateBuffer(context,
        CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        ARRAY_SIZE * sizeof(float), host_b, &err);
    CHECK(err);

    // No source pointer: the kernel will fill this one in.
    cl_mem buffer_result = clCreateBuffer(context,
        CL_MEM_READ_WRITE,
        ARRAY_SIZE * sizeof(float), 0, &err);
    CHECK(err);

    // wire the buffers up to the kernel's parameters (0, 1, 2).
    err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &buffer_a);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &buffer_b);
    err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &buffer_result);
    if (err != CL_SUCCESS) {
        cout << "Cannot set kernel arguments\n";
        return 1;
    }

    
    // 4) Enqueue the kernel to run
    // One work item per array element: global work size = 16.
    // This call is NON-BLOCKING: it just places the kernel in the queue and
    // returns immediately. The kernel has not necessarily run yet!
    size_t globalWorkSize[1] = { ARRAY_SIZE };

    err = clEnqueueNDRangeKernel(commandQueue, kernel,
                                 1,               // number of work dimensions
                                 0,               // global work offset
                                 globalWorkSize,  // total work items
                                 NULL,            // local work size: let OpenCL decide
                                 0, 0, 0);        // no event wait list, no event out
    CHECK(err);

    
    // 5) Get the results back
    // CL_TRUE makes this a BLOCKING read: the host waits here. Because the
    // queue runs in order, the kernel is guaranteed to have finished first.
    // This is our synchronisation point.
    err = clEnqueueReadBuffer(commandQueue, buffer_result,
                              CL_TRUE,                      // blocking
                              0,                            // offset in bytes
                              ARRAY_SIZE * sizeof(float),   // bytes to read
                              host_result,                  // destination (host memory)
                              0, 0, 0);
    CHECK(err);

    // Process the results: expect 0 1 4 9 16 ... 225
    cout << "\nResults (a[i] * b[i]):\n";
    bool allCorrect = true;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        cout << host_a[i] << " * " << host_b[i] << " = " << host_result[i] << "\n";
        if (host_result[i] != host_a[i] * host_b[i]) allCorrect = false;
    }
    cout << (allCorrect ? "\nAll results correct.\n" : "\nMISMATCH - something is wrong!\n");

    
    // Clean up
    // OpenCL objects are reference counted and must be released by hand,
    // roughly in reverse order of creation.
    clReleaseMemObject(buffer_a);
    clReleaseMemObject(buffer_b);
    clReleaseMemObject(buffer_result);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(commandQueue);
    clReleaseProgram(program);
    clReleaseContext(context);
    free(contextDevices);
    free(platformArray);

    return allCorrect ? 0 : 1;
}
