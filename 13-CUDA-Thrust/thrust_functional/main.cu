#include <iostream>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

using namespace std;
using namespace thrust;

host_vector<int> get_vector();

struct is_even {
    __device__ bool operator ()(int item) {
        return item % 2 == 0;
    }
};

struct square {
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
    auto host_data_vector = get_vector();
    device_vector<int> data_vector = host_data_vector;
    device_vector<int> filtered_vector(data_vector.size());
    copy_if(data_vector.begin(), data_vector.end(), filtered_vector.begin(), is_even());
    device_vector<int> squared_vector(filtered_vector.size());
    transform(filtered_vector.begin(), filtered_vector.end(), squared_vector.begin(), square());
    int sum = reduce(squared_vector.begin(), squared_vector.end(), 0, sum_func());
    cout << sum << endl;
    return 0;
}

host_vector<int> get_vector() {
    host_vector<int> result(20);
    for (auto i = 1; i < 21; i++) {
        result.push_back(i);
    }
    return result;
}