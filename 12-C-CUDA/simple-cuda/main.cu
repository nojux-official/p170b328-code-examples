#include "cuda_runtime.h"
#include <cuda.h>
#include <cstdio>
#include <iostream>
#include "device_launch_parameters.h"

using namespace std;

__global__ void run_on_gpu();
__device__ void execute(const char* name);

int main() {
    run_on_gpu<<<1, 2>>>();
    cudaDeviceSynchronize();
    cout << "Finished" << endl;
}

__global__ void run_on_gpu() {
    const char* name;
    if (threadIdx.x == 0) {
        name = "Thread 1";
    } else {
        name = "Thread 2";
    }
    execute(name);
}

__device__ void execute(const char* name) {
    printf("%s: first\n", name);
    printf("%s: second\n", name);
    printf("%s: third\n", name);
}
