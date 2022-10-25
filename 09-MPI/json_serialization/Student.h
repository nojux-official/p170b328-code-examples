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
    static Student from_json(const string& json_string);
    string get_name();
    [[nodiscard]] int get_study_year() const;
    [[nodiscard]] double get_average_grade() const;
    string to_string();
};


#endif //JSON_SERIALIZATION_STUDENT_H
