#include <iostream>
#include <mpi.h>

using namespace std;

// a program that demonstrates basic communication using OpenMPI. Process 0 sends a message to process 1, then process 1
// sends a message to process 0.
int main() {
    MPI::Init();  // initialize MPI; without this we would get an error when calling other MPI functions
    // check rank (process number)
    const auto rank = MPI::COMM_WORLD.Get_rank();
    // check how many processes we have
    const auto total_processes = MPI::COMM_WORLD.Get_size();
    if (rank == 0) {
        // process number 0: send message to process 1 and receive response
        cout << "Process count " << total_processes << endl;
        // get processor name (it actually is a computer name, not CPU name)
        char name[MPI::MAX_PROCESSOR_NAME];
        int name_length = 0;
        MPI::Get_processor_name(name, name_length);
        cout << "Processor name " << name << endl;
        constexpr int sent_message = 0;
        int received_message = 0;
        // in order to send a message, we must pass its address and type: MPI.Send accepts a void pointer as first
        // parameter which means that all type information is lost - we just pass a pointer to memory without specifying
        // which type we are passing. As different types take up different amount of memory, we must pass all this
        // information with 2 more parameters. The send line should be read as: send whatever data is in memory location
        // pointed by &sent_message address, take 1 integer from that location, send it to process number 1 and put tag
        // 1 on the message
        MPI::COMM_WORLD.Send(&sent_message, 1, MPI::INT, 1, 1);
        cout << "Sent message " << sent_message << endl;
        // should be read as: into memory location starting with memory location pointed by &received_message, receive 1
        // integer from process number 1 if it sent tag 1 along with the message.
        MPI::COMM_WORLD.Recv(&received_message, 1, MPI::INT, 1, 1);
        cout << "Received message " << received_message << endl;
    } else {
        constexpr int sent_message = 1;
        // process number 1: get message from process 0 and send response
        int received_message = 1;
        MPI::COMM_WORLD.Recv(&received_message, 1, MPI::INT, 0, 1);
        cout << "Received message " << received_message << endl;
        MPI::COMM_WORLD.Send(&sent_message, 1, MPI::INT, 0, 1);
        cout << "Sent message " << sent_message << endl;
    }
    MPI::Finalize();  // this is needed to properly end the program
    return 0;
}