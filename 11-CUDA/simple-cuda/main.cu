#include "cuda_runtime.h"
#include <iostream>

using namespace std;

__global__ void run_on_gpu();
__device__ void execute(const char* name);

// a program that prints different strings in parallel from GPU
int main() {
    // start function run_on_gpu on one block on two threads concurrently
    run_on_gpu<<<1, 2>>>();
    // wait for device to finish
    cudaDeviceSynchronize();
    cout << "Finished" << endl;
}

// a function that prints some text to console depending on its number. Global function means that it will be called
// from CPU code, but runs on GPU
__global__ void run_on_gpu() {
    const char* name;
    // thread id is between 0 and blockDim (2 in this case)
    if (threadIdx.x == 0) {
        name = "Thread 1";
    } else {
        name = "Thread 2";
    }
    execute(name);
}

// a function that prints some text to console on GPU
__device__ void execute(const char* name) {
    printf("%s: first\n", name);
    printf("%s: second\n", name);
    printf("%s: third\n", name);
}
