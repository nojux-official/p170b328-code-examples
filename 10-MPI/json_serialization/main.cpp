#include <iostream>
#include <mpi.h>
#include "Student.h"

using namespace std;
using namespace MPI;

Student* get_student();

int main() {
    Init();
    auto rank = COMM_WORLD.Get_rank();
    if (rank == 0) {
        auto* student = get_student();
        string serialized = student->to_json();
        int serialized_size = static_cast<int>(serialized.size());
        const char* serialized_chars = serialized.c_str();
        COMM_WORLD.Send(&serialized_size, 1, INT, 1, 0);
        COMM_WORLD.Send(serialized_chars, serialized_size, CHAR, 1, 1);
    } else {
        int size;
        COMM_WORLD.Recv(&size, 1, INT, 0, 0);
        char serialized[size];
        COMM_WORLD.Recv(serialized, size, CHAR, 0, 1);
        auto student = Student::from_json(string(serialized, 0, static_cast<unsigned long>(size)));
        cout << student.get_name() << " " << student.get_average_grade() << " " << student.get_study_year() << endl;
    }
    Finalize();
    return 0;
}

Student *get_student() {
    return new Student("Vardenis Pavardenis", 3, 7.8);
}