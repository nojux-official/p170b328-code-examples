#include <iostream>
#include <mpi.h>

using namespace std;
using namespace MPI;

/* Six processes are required to run this program: 5 sender processes will send a message to the receiver process which
 * collects all messages and outputs them to console.
 * */

string get_message(int rank);

int main() {
    // initialize OpenMPI
    Init();
    // get current process number (0-5)
    if (const auto rank = COMM_WORLD.Get_rank(); rank == 0) {
        // process number 0 is receiver; get process count and receive as many messages as there are processes,
        // excluding this process
        const auto size = COMM_WORLD.Get_size();
        for (int i = 1; i < size; i++) {
            Status status;  // store message status here
            COMM_WORLD.Probe(ANY_SOURCE, 1, status);  // check incoming message status
            char buffer[status.Get_count(CHAR)];  // store received message here
            COMM_WORLD.Recv(buffer, status.Get_count(CHAR), CHAR, status.Get_source(), 1);  // receive the message
            string message(&buffer[0], &buffer[status.Get_count(CHAR)]);
            cout << "Received value " << message << endl;
        }
    } else {
        // processes 1-5 are senders; get message for the sender and send it
        const string message = get_message(rank);
        auto *buffer = message.c_str();
        COMM_WORLD.Send(buffer, static_cast<int>(message.size()), CHAR, 0, 1);
    }
    Finalize();
}

string get_message(const int rank) {
    switch (rank) {
        case 1:
            return "One";
        case 2:
            return "Two";
        case 3:
            return "Three";
        case 4:
            return "Four";
        case 5:
            return "Five";
        default:
            return "";
    }
}
