#include <iostream>
#include <mpi.h>
#include <algorithm>
#include <random>

using namespace std;
using namespace MPI;

const size_t DATA_SIZE = 13000;

const int MAIN_PROCESS = 0;
const int MIN_CALCULATOR = 1;
const int MAX_CALCULATOR = 2;

int get_minimum_value(const int collection[], size_t collection_size);
int get_maximum_value(const int collection[], size_t collection_size);

// Main process generates an array of data. Two other processes compute minimum and maximum values of this array
// respectively. The main process then prints both values to console.

int main() {
    Init();
    auto rank = COMM_WORLD.Get_rank();
    int data[DATA_SIZE];
    if (rank == MAIN_PROCESS) {
        // main process - generate array
        random_device rd;
        default_random_engine dre(rd());
        uniform_int_distribution<int> uid(0, 1000000);
        generate(data, data + sizeof(data) / sizeof(int), [&] { return uid(dre);});
    }
    // Bcast shares the data between all processes - now all processes have data array filled with the same data
    COMM_WORLD.Bcast(data, DATA_SIZE, INT, MAIN_PROCESS);
    switch(rank) {
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
            auto min_value = get_minimum_value(data, DATA_SIZE);
            COMM_WORLD.Send(&min_value, 1, INT, MAIN_PROCESS, 0);
            break;
        }
        case MAX_CALCULATOR: {
            // compute the maximum value and send it to main process
            auto max_value = get_maximum_value(data, DATA_SIZE);
            COMM_WORLD.Send(&max_value, 1, INT, MAIN_PROCESS, 0);
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

/**
 * Gets a minimum value of a given array
 * @param collection - the array to search for minimum
 * @param collection_size - array size
 * @return minimum element of the array
 */
int get_minimum_value(const int collection[], const size_t collection_size) {
    // min_element returns a pointer to the minimum element (its address in memory)
    auto* min = min_element(collection, collection + collection_size);
    // get the value from this memory location and return it
    return *min;
}

/**
 * Gets a maximum value of a given array
 * @param collection - the array to search for minimum
 * @param collection_size - array size
 * @return maximum element of the array
 */
int get_maximum_value(const int collection[], const size_t collection_size) {
    // max_element returns a pointer to the minimum element (its address in memory)
    auto* max = max_element(collection, collection + collection_size);
    // get the value from this memory location and return it
    return *max;
}
