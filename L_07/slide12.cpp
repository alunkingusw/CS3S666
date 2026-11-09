#include <iostream>
#include <tbb/tbb.h>
#include <vector>

void parallel_computation(const tbb::blocked_range<int>& range, int* data) {
    for (int i = range.begin(); i != range.end(); ++i) {
        // Perform some computation on data[i]
        data[i] = data[i] * 2;
    }
}

int main() {
    const int size = 100000;
    int data[size];

for (int i = 0; i < size; ++i) {
        data[i] = i;
    }

tbb::parallel_for(tbb::blocked_range<int>(0, size),
                      [&](const tbb::blocked_range<int>& range) {
                          parallel_computation(range, data);
                      });

for (int i = 0; i < 10; ++i) {
        std::cout << data[i] << " ";
    }

    return 0;
}
