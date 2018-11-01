#ifndef JSON_SERIALIZATION_STUDENT_H
#define JSON_SERIALIZATION_STUDENT_H

#include <string>

using namespace std;

class Student {
private:
    string name;
    int study_year;
    double average_grade;
public:
    Student(string name, int year, double average_grade);
    string to_json();
    static Student from_json(string json_string);
    string get_name();
    int get_study_year();
    double get_average_grade();
};


#endif //JSON_SERIALIZATION_STUDENT_H
