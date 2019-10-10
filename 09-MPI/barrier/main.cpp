#include <iostream>
#include <mpi.h>
#include <random>

using namespace std;
using namespace MPI;

const int MESSAGES_SENT_PER_PROCESS = 50;
const int ROOT_PROCESS = 0;
const int MAX_ITERATIONS = 5;

int main() {
    Init();  // initialize MPI
    auto rank = COMM_WORLD.Get_rank();  // get process rank
    auto process_count = COMM_WORLD.Get_size();  // get process count
    auto count = 0;  // we will increment this value in process 0
    // calculate the amount of received messages per iteration
    auto messages_received = (process_count - 1) * MESSAGES_SENT_PER_PROCESS;
    // initialize random number generator
    random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<mt19937::result_type> dist(1,85000);
    for (auto iteration = 0; iteration <= MAX_ITERATIONS; iteration++) {
        if (rank == ROOT_PROCESS) {
            // if it's root process, receive messages from other processes and add all of them to count
            for (auto i = 0; i < messages_received; i++) {
                int increment_by;
                COMM_WORLD.Recv(&increment_by, 1, INT, ANY_SOURCE, ANY_TAG);
                count += increment_by;
            }
        } else {
            // if it's not root, generate random numbers and send them to root process
            for (auto i = 0; i < MESSAGES_SENT_PER_PROCESS; i++) {
                auto increment_by = dist(rng);
                COMM_WORLD.Send(&increment_by, 1, INT, ROOT_PROCESS, 0);
            }
        }
        if (rank == 0) {
            // print current value of count
            cout << count << endl;
        }
        // no process may proceed to next iteration until all processes call Barrier method
        COMM_WORLD.Barrier();
    }
    Finalize();
    return 0;
}