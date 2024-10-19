#include <algorithm>
#include <iostream>
#include <mpi.h>
#include <numeric>

using namespace std;
using namespace MPI;

constexpr int MAIN_PROCESS = 0;

constexpr auto NUM_PER_PROCESS = 6;

/// main process generates an array of integers and splits them evenly between the processes
int main() {
    Init();
    const auto total_processes = COMM_WORLD.Get_size();
    const auto data_size = total_processes * NUM_PER_PROCESS;
    // full_data only has to be initialized in the main processes, all others will have a nullptr value for it
    int* full_data = nullptr;
    const auto rank = COMM_WORLD.Get_rank();
    if (rank == MAIN_PROCESS) {
        // initialize the array and fill it with numbers from 0 to data_size
        full_data = new int[data_size];
        iota(full_data, full_data + data_size, 0);
    }
    // initialize an array for one chunk of data
    int chunk[NUM_PER_PROCESS];
    // distribute data from MAIN_PROCESS full_data array to every process chunk array
    COMM_WORLD.Scatter(full_data, NUM_PER_PROCESS, INT, chunk, NUM_PER_PROCESS, INT, MAIN_PROCESS);
    Finalize();

    // print the received chunk
    cout << "Process " << rank << " received ";
    for_each(chunk, chunk + NUM_PER_PROCESS, [](auto num) {cout << num << " ";});
    cout << endl;
    // free up initialized data array
    delete[] full_data;
}