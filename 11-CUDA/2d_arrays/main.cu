#include "cuda_runtime.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>

using namespace std;

constexpr size_t ARRAY_SIZE = 100;
constexpr size_t INNER_ARRAY_SIZE = 50;
constexpr size_t FULL_ARRAY_SIZE = ARRAY_SIZE * INNER_ARRAY_SIZE;

void generate_random_array(int *array, size_t size);
void print_matrix(const int* matrix);
__global__ void get_doubled_matrix(const int* original, int* result);

// a program that demonstrates how to use blocks and threads to multiply all elements in a matrix by 2.
int main() {
    const auto flat_matrix = new int[FULL_ARRAY_SIZE];  // matrix will be held in a flat array
    // pointers that will be assigned by cuda memory allocation
    int* flat_matrix_device;
    int* doubled_matrix;
    // result will be held in this array
    const auto doubled_matrix_host = new int[FULL_ARRAY_SIZE];
    // fill array with random values
    generate_random_array(flat_matrix, FULL_ARRAY_SIZE);
    // output what we generated
    print_matrix(flat_matrix);

    // make memory on GPU to fit our original data and write the address of that memory to flat_matrix_device pointer
    cudaMalloc(&flat_matrix_device, FULL_ARRAY_SIZE * sizeof(int));
    // copy to flat_matrix_device from flat_matrix (from CPU to GPU memory)
    cudaMemcpy(flat_matrix_device, flat_matrix, FULL_ARRAY_SIZE * sizeof(int), cudaMemcpyHostToDevice);
    // make memory on GPU for our result
    cudaMalloc(&doubled_matrix, FULL_ARRAY_SIZE * sizeof(int));

    // launch ARRAY_SIZE blocks on GPU, each block containing INNER_ARRAY_SIZE of threads.
    get_doubled_matrix<<<ARRAY_SIZE, INNER_ARRAY_SIZE>>>(flat_matrix_device, doubled_matrix);
    // wait for CUDA operations to finish
    cudaDeviceSynchronize();

    // retrieve our result from GPU
    cudaMemcpy(doubled_matrix_host, doubled_matrix, FULL_ARRAY_SIZE * sizeof(int), cudaMemcpyDeviceToHost);
    // destroy allocated memory on GPU, we no longer need it
    cudaFree(flat_matrix_device);
    cudaFree(doubled_matrix);

    // some pretty output
    cout << setfill('-') << setw(INNER_ARRAY_SIZE * 4) << "" << endl << setfill(' ');
    print_matrix(doubled_matrix_host);

    // destroy allocated memory on CPU
    delete[] flat_matrix;
    delete[] doubled_matrix_host;

    return 0;
}

// a function that fills an array with random values
void generate_random_array(int *array, size_t size) {
    random_device dev;
    default_random_engine engine(dev());
    uniform_int_distribution<int> uniform_dist(0, 100);
    generate(array, &array[size], [&] { return uniform_dist(engine); });
}

// a function that prints a matrix nicely to console
void print_matrix(const int* matrix) {
    for (auto i = 0; i < ARRAY_SIZE; i++) {
        for (auto j = 0; j < INNER_ARRAY_SIZE; j++) {
            const auto index = INNER_ARRAY_SIZE * i + j;
            cout << setw(4) << matrix[index];
        }
        cout << endl;
    }
}

// Function that is run on GPU as many times as there elements in our matrix. One thread computes one element in the 
// result matrix.
__global__ void get_doubled_matrix(const int* original, int* result) {
    const auto index = blockIdx.x * blockDim.x + threadIdx.x;
    result[index] = original[index] * 2;
}
