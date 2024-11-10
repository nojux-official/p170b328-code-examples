#include "cuda_runtime.h"
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

constexpr int ARRAY_SIZE = 100;

void generate_random_array(int* array, size_t size);
__global__ void add(const int* a, const int* b, int* c);

int main() {
    int first[ARRAY_SIZE], second[ARRAY_SIZE], sum[ARRAY_SIZE];
    generate_random_array(first, ARRAY_SIZE);
    generate_random_array(second, ARRAY_SIZE);
    int *device_first, *device_second, *device_sum;
    constexpr int size = ARRAY_SIZE * sizeof(int);
    cudaMalloc(&device_first, size);
    cudaMalloc(&device_second, size);
    cudaMalloc(&device_sum, size);
    cudaMemcpy(device_first, first, size, cudaMemcpyHostToDevice);
    cudaMemcpy(device_second, second, size, cudaMemcpyHostToDevice);
    add<<<1, ARRAY_SIZE>>>(device_first, device_second, device_sum);
    cudaDeviceSynchronize();
    cudaMemcpy(sum, device_sum, size, cudaMemcpyDeviceToHost);
    cudaFree(device_first);
    cudaFree(device_second);
    cudaFree(device_sum);
    for_each(sum, &sum[ARRAY_SIZE], [](const int &n) { cout << n << endl;});
    return 0;
}

void generate_random_array(int *array, size_t size) {
    random_device dev;
    default_random_engine engine(dev());
    uniform_int_distribution<int> uniform_dist(0, 100);
    generate(array, &array[size], [&] { return uniform_dist(engine); });
}

__global__ void add(const int* a, const int* b, int* c) {
    if (const auto thread_id = threadIdx.x; thread_id < ARRAY_SIZE) {
        c[thread_id] = a[thread_id] + b[thread_id];
    }
}
