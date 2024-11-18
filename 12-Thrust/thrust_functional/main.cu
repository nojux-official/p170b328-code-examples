#include <iostream>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/copy.h>

using namespace std;

thrust::host_vector<int> get_vector();

struct is_even {
    __device__ bool operator ()(int item) {
        return item % 2 == 0;
    }
};

struct square_func {
    __device__ int operator ()(int item) {
        return item * item;
    }
};

struct sum_func {
    __device__ int operator ()(int accumulator, int item) {
        return accumulator + item;
    }
};

int main() {
    const auto host_data_vector = get_vector();
    thrust::device_vector<int> data_vector = host_data_vector;
    thrust::device_vector<int> filtered_vector(data_vector.size());
    thrust::copy_if(data_vector.begin(), data_vector.end(), filtered_vector.begin(), is_even());
    thrust::device_vector<int> squared_vector(filtered_vector.size());
    thrust::transform(filtered_vector.begin(), filtered_vector.end(), squared_vector.begin(), square_func());
    int sum = reduce(squared_vector.begin(), squared_vector.end(), 0, sum_func());
    cout << sum << endl;
    return 0;
}

thrust::host_vector<int> get_vector() {
    thrust::host_vector<int> result(20);
    for (auto i = 1; i < 21; i++) {
        result.push_back(i);
    }
    return result;
}