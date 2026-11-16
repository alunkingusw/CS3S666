kernel void hello_kernel(
    global const float *a,      // input buffer  (device global memory)
    global const float *b,      // input buffer  (device global memory)
    global float *result)       // output buffer (device global memory)
{
    int gid = get_global_id(0);     // dim_index 0 = first (and only) dimension

    // Needs a device/driver that supports printf in kernels (OpenCL 1.2+).
     printf("work item %d running\n", gid);

    result[gid] = a[gid] * b[gid];
}
