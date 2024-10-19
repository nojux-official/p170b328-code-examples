#include <iostream>
#include <mpi.h>
#include "Student.h"

using namespace std;
using namespace MPI;

Student* get_student();

int main() {
    Init();
    if (const auto rank = COMM_WORLD.Get_rank(); rank == 0) {
        auto* student = get_student();
        const string serialized = student->to_json();
        const auto serialized_size = serialized.size();
        const char* serialized_chars = serialized.c_str();
        COMM_WORLD.Send(serialized_chars, static_cast<int>(serialized_size), CHAR, 1, 1);
    } else {
        Status status;
        COMM_WORLD.Probe(0, 1, status);
        const auto size = status.Get_count(CHAR);
        char serialized[size];
        COMM_WORLD.Recv(serialized, size, CHAR, 0, 1);
        auto student = Student::from_json(string(serialized, serialized + size));
        cout << student.to_string() << endl;
    }
    Finalize();
    return 0;
}

Student *get_student() {
    return new Student("Vardenis Pavardenis", 3, 7.8);
}