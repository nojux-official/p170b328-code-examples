#include <iostream>
#include <mpi.h>

using namespace std;
using namespace MPI;

struct Student {
    char name[50];
    double average_grade;
    int study_year;
};

Student* get_student();

int main() {
    Init();
    auto rank = COMM_WORLD.Get_rank();
    if (rank == 0) {
        auto* student = get_student();
        cout << student->name << " year: " << student->study_year << "; average " << student->average_grade << endl;
        int student_size = sizeof(Student);
        COMM_WORLD.Send(&student_size, 1, INT, 1, 0);
        auto* serialized_student = (char*) student;
        COMM_WORLD.Send(serialized_student, student_size, CHAR, 1, 1);
    } else {
        int student_size;
        COMM_WORLD.Recv(&student_size, 1, INT, 0, 0);
        char serialized_student[student_size];
        COMM_WORLD.Recv(serialized_student, student_size, CHAR, 0, 1);
        auto* student = (Student*) serialized_student;
        cout << student->name << " year: " << student->study_year << "; average " << student->average_grade << endl;
    }
    Finalize();
    return 0;
}

Student* get_student() {
    auto * student = new Student;
    string name = "Vardenis Pavardenis";
    name.copy(student->name, name.size());
    student->average_grade = 7.8;
    student->study_year = 3;
    return student;
}