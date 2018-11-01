#include <iostream>
#include <mpi.h>

using namespace std;
using namespace MPI;

const int MESSAGES_SENT_PER_PROCESS = 50;

int main() {
    Init();
    auto rank = COMM_WORLD.Get_rank();
    auto process_count = COMM_WORLD.Get_size();
    auto count = 0;
    auto messages_received = (process_count - 1) * MESSAGES_SENT_PER_PROCESS;
    for (auto message = 1; message <= 2; message++) {
        if (rank == 0) {
            for (auto i = 0; i < messages_received; i++) {
                int increment_by;
                COMM_WORLD.Recv(&increment_by, 1, INT, ANY_SOURCE, ANY_TAG);
                count += increment_by;
            }
        } else {
            for (auto i = 0; i < MESSAGES_SENT_PER_PROCESS; i++) {
                COMM_WORLD.Send(&message, 1, INT, 0, 0);
            }
        }
        if (rank == 0) {
            cout << count << endl;
        }
        COMM_WORLD.Barrier();
    }
    Finalize();
    return 0;
}