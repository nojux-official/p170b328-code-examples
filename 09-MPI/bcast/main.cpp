#include <iostream>
#include <mpi.h>
#include <algorithm>
#include <random>

using namespace std;
using namespace MPI;

const int DATA_SIZE = 10000;

int get_minimum_value(const int collection[], int collection_size);
int get_maximum_value(const int collection[], int collection_size);

int main() {
    Init();
    auto rank = COMM_WORLD.Get_rank();
    int data[DATA_SIZE];
    if (rank == 0) {
        random_device rd;
        default_random_engine dre(rd());
        uniform_int_distribution<int> uid(0, 1000000);
        generate(data, data + sizeof(data) / sizeof(int), [&] { return uid(dre);});
    }
    COMM_WORLD.Bcast(data, DATA_SIZE, INT, 0);
    switch(rank) {
        case 0: {
            auto min = 0;
            auto max = 0;
            COMM_WORLD.Recv(&min, 1, INT, 1, 0);
            COMM_WORLD.Recv(&max, 2, INT, 2, 0);
            cout << "minimum value " << min << endl;
            cout << "maximum value " << max << endl;
            break;
        }
        case 1: {
            auto min_value = get_minimum_value(data, DATA_SIZE);
            COMM_WORLD.Send(&min_value, 1, INT, 0, 0);
            break;
        }
        case 2: {
            auto max_value = get_maximum_value(data, DATA_SIZE);
            COMM_WORLD.Send(&max_value, 1, INT, 0, 0);
            break;
        }
        default: {
            cerr << "Unexpected amount of processes launched" << endl;
        }
    }
    Finalize();
    return 0;
}

int get_minimum_value(const int collection[], const int collection_size) {
    return accumulate(collection, collection + collection_size, numeric_limits<int>::max(), [](int acc, int val) {
        return val < acc ? val : acc;
    });
}

int get_maximum_value(const int collection[], const int collection_size) {
    return accumulate(collection, collection + collection_size, numeric_limits<int>::min(), [](int acc, int val) {
        return val > acc ? val : acc;
    });
}
