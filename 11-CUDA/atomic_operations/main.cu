#include <iostream>
#include <random>

using namespace std;

void generate_data(int* data, size_t count);
__global__ void get_sum(const int *data, const size_t* count, int* sum);


/// The example randomly generates a huge array of ints and computes its sum on the GPU.

int main() {
    constexpr size_t ARRAY_SIZE = 10000000;
    // create an array that holds a large number of integers and fill it with data
    auto numbers = new int[ARRAY_SIZE];
    generate_data(numbers, ARRAY_SIZE);
    int initial_sum = 0; // this value is the initial value for sum: we start from zero and then add numbers to it

    // pointers that will point to device memory
    int *device_numbers, *device_sum;
    size_t *device_count;

    // allocate space for the array, array size and result. Before cudaMallocs the pointers are null pointers,
    // cudaMalloc changes their value to some GPU memory address, so we need to pass the address of the pointer, not the
    // pointer itself
    cudaMalloc(&device_numbers, ARRAY_SIZE * sizeof(int));  // allocate memory chuck for the array
    cudaMalloc(&device_count, sizeof(size_t));  // allocate memory for array size (one size_t)
    cudaMalloc(&device_sum, sizeof(int));  // allocate memory for the result (one int)

    // copy data from RAM to VRAM
    cudaMemcpy(device_numbers, numbers, ARRAY_SIZE * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(device_count, &ARRAY_SIZE, sizeof(size_t), cudaMemcpyHostToDevice);
    cudaMemcpy(device_sum, &initial_sum, sizeof(int), cudaMemcpyHostToDevice);

    // get device properties, we will use it to launch the maximum available number of threads
    cudaDeviceProp prop{};
    cudaGetDeviceProperties(&prop, 0);

    // run get_sum on GPU
    get_sum<<<1, prop.maxThreadsPerBlock>>>(device_numbers, device_count, device_sum);

    int sum = 0;
    // get sum from VRAM
    cudaMemcpy(&sum, device_sum, sizeof(int), cudaMemcpyDeviceToHost);
    cout << sum << endl;

    // free all memory on the heap and VRAM
    delete [] numbers;
    cudaFree(device_numbers);
    cudaFree(device_sum);
    cudaFree(device_count);
}

/// given an array and its size, fills it with random numbers from 0 to 1000
/// \param data - an array to fill
/// \param count - size of the array
void generate_data(int *data, const size_t count) {
    random_device rand;
    mt19937 rng(rand());
    uniform_int_distribution<int> uni(0, 1000);
    for (auto i = 0; i < count; i++) {
        data[i] = uni(rng);
    }
}

/// Computes the partial sum of the data array and adds it to the global sum
/// \param data - an array to get sum for
/// \param count - size of the array
/// \param sum - the global sum, this is the result of this function
__global__ void get_sum(const int *data, const size_t* count, int* sum) {
    // one thread processes one slice of data. Slice size is equal to total count divided by number of threads
    const auto slice_size = *count / blockDim.x;
    // compute start index
    const unsigned long start_index = slice_size * threadIdx.x;
    // compute end index. Last thread takes all remaining elements in case they are not split evenly between threads
    unsigned long end_index;
    if (threadIdx.x == blockDim.x - 1) {
        end_index = *count;
    } else {
        end_index = slice_size * (threadIdx.x + 1);
    }
    // compute sum of the chunk of the array
    auto local_sum = 0;
    for (auto i = start_index; i < end_index; i++) {
        local_sum += data[i];
    }
    // add the local sum to the global sum. This modifies shared (global) memory, so update it atomically
    atomicAdd(sum, local_sum);
}
