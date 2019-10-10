#include <iostream>
#include <mpi.h>
#include <algorithm>

using namespace MPI;
using namespace std;

const int ITEM_COUNT = 15;
const int ROOT_PROCESS = 0;

// A program that demonstrates how MPI_Reduce works. Each process has an array of 15 elements fill in some way. At 
// first, we find the largest element at each index across all processes using MPI, then we find global maximum using
// standard C++.
int main() {
    Init();  // initialize MPI
    int items[ITEM_COUNT];  // data of each process
    auto rank = COMM_WORLD.Get_rank();  // check current process ID
    // fill the array in some way
    for (auto i = 0; i < ITEM_COUNT; i++) {
        items[i] = i * i * (rank + 1);
    }
    int results[ITEM_COUNT];  // results will be stored in this array, only relevant to root process
    // call MPI_Reduce. This will write to results array on ROOT_PROCESS process. results[0] will contain the maximum
    // value of all items[0] of each process, results[1] - maximum of items[1] etc.
    COMM_WORLD.Reduce(items, results, ITEM_COUNT, INT, MAX, ROOT_PROCESS);
    if (rank == ROOT_PROCESS) { // if it's root process, it will contain our results
        for_each(results, results + ITEM_COUNT, [](auto item) {
            cout << item << endl;  // print results to console
        });
        // also find the maximum of all maxima we collected. This does not use MPI, but is here for the sake of
        // completeness :)
        auto global_maximum = max_element(results, results + ITEM_COUNT);
        cout << "Global maximum: " << *global_maximum << endl;  // global_maximum is a pointer and has to be deferenced
    }
    Finalize();  // shut down MPI so it does not crash at the end
    return 0;
}