#include <iostream>
#include <mpi.h>
#include <random>

using namespace std;
using namespace MPI;

void calculate_full_sum();
void calculate_partial_sum();

const int MAIN_PROCESS = 0;

int main() {
    Init();
    auto rank = COMM_WORLD.Get_rank();
    if (rank == 0) {
        calculate_full_sum();
    } else {
        calculate_partial_sum();
    }
    Finalize();
    return 0;
}

void calculate_full_sum() {
    auto worker_count = COMM_WORLD.Get_size() - 1;
    const auto DATA_SIZE = 13000;
    int numbers[DATA_SIZE];
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, 1000);
    int partial_sums[worker_count];
    for (int &number : numbers) {
        number = uni(rng);
    }
    auto chunk_size = DATA_SIZE / worker_count;
    for (auto i = 0; i < worker_count; i++) {
        int end_index = (i == worker_count - 1 ? DATA_SIZE - 1: (i+1) * chunk_size - 1);
        int start_index = i * chunk_size;
        int current_chunk_size = end_index - start_index;
        COMM_WORLD.Send(numbers + start_index, current_chunk_size, INT, i + 1, 2);
    }
    for (auto i = 0; i < worker_count; i++) {
        COMM_WORLD.Recv(&partial_sums[i], 1, INT, ANY_SOURCE, 1);
    }
    auto total_sum = accumulate(&partial_sums[0], &partial_sums[worker_count], 0,  [](int x, int y) { return x + y;});
    cout << total_sum << endl;
}

void calculate_partial_sum() {
    Status status;
    COMM_WORLD.Probe(MAIN_PROCESS, ANY_TAG, status);
    const auto item_count = status.Get_count(INT);
    int items[item_count];
    COMM_WORLD.Recv(items, item_count, INT, 0, ANY_TAG);
    auto total_sum = accumulate(items, items + item_count, 0, [](int x, int y) { return x + y;});
    COMM_WORLD.Send(&total_sum, 1, INT, 0, 1);
}
