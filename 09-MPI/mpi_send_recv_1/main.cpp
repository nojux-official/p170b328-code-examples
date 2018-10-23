#include <iostream>
#include <mpi.h>

using namespace std;

int main() {
    MPI::Init();
    char name[MPI::MAX_PROCESSOR_NAME];
    int name_length = 0;
    MPI::Get_processor_name(name, name_length);
    auto rank = MPI::COMM_WORLD.Get_rank();
    auto totalProcesses = MPI::COMM_WORLD.Get_size();
    if (rank == 0) {
        cout << "Process count " << totalProcesses << endl;
        cout << "Processor name " << name << endl;
        int sent_message = 0, received_message = 0;
        MPI::COMM_WORLD.Send(&sent_message, 1, MPI::INT, 1, 1);
        cout << "Sent message " << sent_message << endl;
        MPI::COMM_WORLD.Recv(&received_message, 1, MPI::INT, 1, 1);
        cout << "Received message " << received_message << endl;
    } else {
        int sent_message = 1, received_message = 1;
        MPI::COMM_WORLD.Recv(&received_message, 1, MPI::INT, 0, 1);
        cout << "Received message " << received_message << endl;
        MPI::COMM_WORLD.Send(&sent_message, 1, MPI::INT, 0, 1);
        cout << "Sent message " << sent_message << endl;
    }
    MPI::Finalize();
    return 0;
}