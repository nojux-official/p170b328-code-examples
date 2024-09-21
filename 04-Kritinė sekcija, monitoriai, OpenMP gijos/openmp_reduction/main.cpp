#include <iostream>
#include <omp.h>
#include <random>

using namespace std;

constexpr size_t ARRAY_SIZE = 2147483;

void fill_array_with_random_numbers(int *arr, size_t size);

int main() {
    const auto numbers = new int[ARRAY_SIZE];
    fill_array_with_random_numbers(numbers, ARRAY_SIZE);
    int sum;
    // calculate sum of numbers by splitting array into as many chunks as we have threads, calculate each sum separately
    // and then get the full sum using reduction directive
#pragma omp parallel reduction(+:sum) default(none) shared(numbers)
    {
        const auto total_threads = omp_get_num_threads();
        const auto chunk_size = ARRAY_SIZE / total_threads;
        const auto thread_number = omp_get_thread_num();
        const auto start_index = chunk_size * thread_number;
        const auto end_index = thread_number == total_threads - 1 ? ARRAY_SIZE - 1 : (thread_number + 1) * chunk_size - 1;
        sum = accumulate(numbers + start_index, numbers + end_index, 0,
                         [](const int acc, const int curr) { return acc + curr; });

    }
    cout << sum << endl;
    delete[] numbers;
}

void fill_array_with_random_numbers(int *arr, const size_t size) {
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, 1000);
    for (auto i = 0; i < size; i++) {
        arr[i] = uni(rng);
    }
}