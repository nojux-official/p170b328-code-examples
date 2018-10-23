#include <iostream>
#include <mpi.h>

using namespace std;
using namespace MPI;

int main() {
    Init();
    string messages[] = {"One", "Two", "Three", "Four", "Five"};
    int size = COMM_WORLD.Get_size();
    auto rank = COMM_WORLD.Get_rank();
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            char buffer[5];
            Status status;
            COMM_WORLD.Probe(ANY_SOURCE, 1, status);
            COMM_WORLD.Recv(buffer, sizeof(buffer), CHAR, ANY_SOURCE, 1);
            string message(&buffer[0], &buffer[status.Get_count(CHAR)]);
            cout << "Received value " << message << endl;
        }
    } else {
        auto message = messages[rank - 1];
        COMM_WORLD.Send(message.c_str(), static_cast<int>(message.size()), CHAR, 0, 1);
    }
    Finalize();
}