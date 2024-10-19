#include <algorithm>
#include <iostream>
#include <mpi.h>
#include <numeric>

using namespace std;
using namespace MPI;

constexpr auto NUM_PER_PROCESS = 6;
constexpr auto MAIN_PROCESS = 0;

int main() {
    int chunk[NUM_PER_PROCESS];
    int *full_data = nullptr;
    int data_size;
    Init();
    const auto rank = COMM_WORLD.Get_rank();
    const auto start_number = rank * NUM_PER_PROCESS;
    iota(chunk, chunk + NUM_PER_PROCESS, start_number);
    if (rank == MAIN_PROCESS) {
        data_size = COMM_WORLD.Get_size() * NUM_PER_PROCESS;
        full_data = new int[data_size];
    }
    COMM_WORLD.Gather(chunk, NUM_PER_PROCESS, INT, full_data, NUM_PER_PROCESS, INT, MAIN_PROCESS);
    Finalize();
    if (rank == MAIN_PROCESS) {
        cout << "Main process received values: ";
        for_each(full_data, full_data + data_size, [](auto num) { cout << num << " "; });
        cout << endl;
        delete[] full_data;
    }
    return 0;
}

