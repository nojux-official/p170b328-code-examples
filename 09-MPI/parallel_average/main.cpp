#include <iostream>
#include <mpi.h>
#include <random>
#include <algorithm>

using namespace std;
using namespace MPI;

constexpr auto ELEMENTS_PER_PROCESS = 143;
constexpr auto MAIN_PROCESS = 0;

double get_average(const double* data, int data_size);

void generate_random_numbers(double *random_numbers, int total_elements);

/// This program generates an array on the MAIN_PROCESS, distributes the data to all processes, each process finds the
/// average of its chunk, all averages are then sent back to MAIN_PROCESS, which then finds the global average
int main() {
    // random_numbers is an array that is only allocated on the MAIN_PROCESS and filled with random numbers, and null on
    // all other processes
    double* random_numbers = nullptr;
    Init();
    const auto t1 = Wtime();
    const auto rank = COMM_WORLD.Get_rank();
    const auto total_processes = COMM_WORLD.Get_size();
    if (rank == MAIN_PROCESS) {
        const auto total_elements = ELEMENTS_PER_PROCESS * total_processes;
        random_numbers = new double[total_elements];
        generate_random_numbers(random_numbers, total_elements);
    }
    double random_numbers_chunk[ELEMENTS_PER_PROCESS];
    COMM_WORLD.Scatter(random_numbers, ELEMENTS_PER_PROCESS, DOUBLE, random_numbers_chunk, ELEMENTS_PER_PROCESS, DOUBLE, 0);
    const double average = get_average(random_numbers_chunk, ELEMENTS_PER_PROCESS);
    double* averages_of_chunks = nullptr;
    if (rank == 0) {
        delete[] random_numbers;
        averages_of_chunks = new double[total_processes];
    }
    COMM_WORLD.Gather(&average, 1, DOUBLE, averages_of_chunks, 1, DOUBLE, 0);
    Finalize();
    if (rank == 0) {
        const auto total_average = get_average(averages_of_chunks, total_processes);
        cout << "average: " << total_average << endl;
        delete[] averages_of_chunks;
    }
    const auto t2 = Wtime();
    const auto time = t2 - t1;
    cout << "MPI time: " << time << " seconds" << endl;
    return 0;
}

void generate_random_numbers(double *random_numbers, const int total_elements) {
    random_device rd;
    default_random_engine dre(rd());
    uniform_real_distribution<double> urd(0, 1000);
    generate_n(random_numbers, total_elements, [&] { return urd(dre);});
}

double get_average(const double *data, int data_size) {
    const double sum = accumulate(data, &data[data_size], 0.0);
    return sum / data_size;
}