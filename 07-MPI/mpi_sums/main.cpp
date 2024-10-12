#include <iostream>
#include <mpi.h>
#include <random>

using namespace std;
using namespace MPI;

void calculate_full_sum();
void calculate_partial_sum();

constexpr auto MAIN_PROCESS = 0;
constexpr auto TAG_PARTIAL_ARRAY = 2;
constexpr auto TAG_PARTIAL_SUM = 1;
constexpr auto DATA_SIZE = 14300;

int main() {
    Init();
    if (const auto rank = COMM_WORLD.Get_rank(); rank == MAIN_PROCESS) {
        calculate_full_sum();
    } else {
        calculate_partial_sum();
    }
    Finalize();
    return 0;
}

/**
 * Manages the computations to split the array into chunks, send them to different processes and collect the results
 * back
 */
void calculate_full_sum() {
    // all processes except this one is a worker, so worker count is the total amount of processes excluding current
    // process
    const auto worker_count = COMM_WORLD.Get_size() - 1;
    //generate an array of random numbers
    int numbers[DATA_SIZE];
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution uni(0, 1000);
    for (int &number : numbers) {
        number = uni(rng);
    }
    const auto chunk_size = DATA_SIZE / worker_count;
    for (auto i = 0; i < worker_count; i++) {
        // send one part of the array to one of the processes. The array chunk indexes are from start_index to
        // end_index. If the data cannot be split evenly, the remainder goes to the last process.
        const int end_index = i == worker_count - 1 ? DATA_SIZE - 1: (i+1) * chunk_size - 1;
        const int start_index = i * chunk_size;
        const int current_chunk_size = end_index - start_index;
        COMM_WORLD.Send(numbers + start_index, current_chunk_size, INT, i + 1, TAG_PARTIAL_ARRAY);
    }
    int partial_sums[worker_count];
    for (auto i = 0; i < worker_count; i++) {
        // collect the partials sums back and store them in a local array of partial sums
        COMM_WORLD.Recv(&partial_sums[i], 1, INT, ANY_SOURCE, TAG_PARTIAL_SUM);
    }
    const auto total_sum = accumulate(partial_sums, partial_sums + worker_count, 0,
        [](const int x, const int y) { return x + y;});
    cout << total_sum << endl;
}

/**
 * Receives an array of integers, computes the sum of the array and sends the sum as a response
 */
void calculate_partial_sum() {
    Status status;
    COMM_WORLD.Probe(MAIN_PROCESS, TAG_PARTIAL_ARRAY, status);
    const auto item_count = status.Get_count(INT);
    int items[item_count];
    COMM_WORLD.Recv(items, item_count, INT, status.Get_source(), status.Get_tag());
    const auto total_sum = accumulate(items, items + item_count, 0,
        [](const int x, const int y) { return x + y;});
    COMM_WORLD.Send(&total_sum, 1, INT, MAIN_PROCESS, TAG_PARTIAL_SUM);
}
