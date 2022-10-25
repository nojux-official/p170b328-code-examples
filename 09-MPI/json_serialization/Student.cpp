#include <utility>

//
// Created by ryselis on 18.11.1.
//

#include "Student.h"
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

Student::Student(string name, int year, double average_grade) {
    this->name = std::move(name);
    this->study_year = year;
    this->average_grade = average_grade;
}

string Student::to_json() {
    json j;
    j["name"] = name;
    j["study_year"] = study_year;
    j["average_grade"] = average_grade;
    return j.dump();
}

Student Student::from_json(const string& json_string) {
    auto parsed = json::parse(json_string);
    return {parsed["name"], parsed["study_year"], parsed["average_grade"]};
}

string Student::get_name() {
    return name;
}

int Student::get_study_year() const {
    return study_year;
}

double Student::get_average_grade() const {
    return average_grade;
}

string Student::to_string() {
    stringstream ss;
    ss << get_name() << " " << get_average_grade() << " " << get_study_year();
    return ss.str();
}
