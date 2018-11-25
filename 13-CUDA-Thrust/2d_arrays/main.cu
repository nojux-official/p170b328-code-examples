#include "cuda_runtime.h"
#include <cuda.h>
#include <cstdio>
#include <iostream>
#include "device_launch_parameters.h"
#include <random>
#include <algorithm>

using namespace std;

const int ARRAY_SIZE = 100;
const int INNER_ARRAY_SIZE = 50;

void generate_random_array(int *array, size_t size);

int main() {
    int* two_dim_array1[ARRAY_SIZE];
    int** two_dim_array1_device = nullptr;
    for (auto &item: two_dim_array1) {
        int inner_array[INNER_ARRAY_SIZE];
        generate_random_array(inner_array, INNER_ARRAY_SIZE);
        item = inner_array;
    }
    cudaMalloc((void**)&two_dim_array1_device, ARRAY_SIZE * sizeof(int*));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        int* item_ptr = nullptr;
        cudaMalloc((void**)&item_ptr, INNER_ARRAY_SIZE * sizeof(int));
        cudaMemcpy(item_ptr, &two_dim_array1[i], INNER_ARRAY_SIZE * sizeof(int), cudaMemcpyHostToDevice);
        cudaMemcpy(&two_dim_array1_device[i], &item_ptr, sizeof(int*), cudaMemcpyHostToDevice);
    }
    return 0;
}

void generate_random_array(int *array, size_t size) {
    random_device dev;
    default_random_engine engine(dev());
    uniform_int_distribution<int> uniform_dist(0, 100);
    generate(array, &array[size], [&] { return uniform_dist(engine); });
}