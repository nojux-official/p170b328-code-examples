#include <iostream>
#include <mpi.h>
#include <algorithm>
#include <random>

using namespace std;
using namespace MPI;

constexpr size_t DATA_SIZE = 13000;

constexpr int MAIN_PROCESS = 0;
constexpr int MIN_CALCULATOR = 1;
constexpr int MAX_CALCULATOR = 2;

// Main process generates an array of data. Two other processes compute minimum and maximum values of this array
// respectively. The main process then prints both values to console.

int main() {
    Init();
    const auto rank = COMM_WORLD.Get_rank();
    int data[DATA_SIZE];
    if (rank == MAIN_PROCESS) {
        // main process - generate array
        random_device rd;
        default_random_engine dre(rd());
        uniform_int_distribution<int> uid(0, 1000000);
        generate_n(data, sizeof(data) / sizeof(int), [&] { return uid(dre); });
    }
    // Bcast shares the data between all processes - now all processes have data array filled with the same data
    COMM_WORLD.Bcast(data, DATA_SIZE, INT, MAIN_PROCESS);
    switch (rank) {
        case MAIN_PROCESS: {
            auto min = 0;
            auto max = 0;
            // receive min and max values from other processes
            COMM_WORLD.Recv(&min, 1, INT, MIN_CALCULATOR, 0);
            COMM_WORLD.Recv(&max, 2, INT, MAX_CALCULATOR, 0);
            // print results
            cout << "minimum value " << min << endl;
            cout << "maximum value " << max << endl;
            break;
        }
        case MIN_CALCULATOR: {
            // compute the minimum value and send it to main process
            const auto *min_value = min_element(data, data + DATA_SIZE);
            COMM_WORLD.Send(min_value, 1, INT, MAIN_PROCESS, 0);
            break;
        }
        case MAX_CALCULATOR: {
            // compute the maximum value and send it to main process
            const auto *max_value = max_element(data, data + DATA_SIZE);
            COMM_WORLD.Send(max_value, 1, INT, MAIN_PROCESS, 0);
            break;
        }
        default: {
            // woops, we do not support such amount of processes
            cerr << "Unexpected amount of processes launched" << endl;
        }
    }
    Finalize();
    return 0;
}
