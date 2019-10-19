//
// Created by ryselis on 2019-10-19.
//

#ifndef OBJECT_REFERENCES_ANIMAL_H
#define OBJECT_REFERENCES_ANIMAL_H

#include <string>
#include <utility>

using namespace std;

class Animal {
private:
    string name;
    string species;
public:
    Animal(string name, string species): name(move(name)), species(move(species)) {};
    string get_name();
    string get_species();
};


#endif //OBJECT_REFERENCES_ANIMAL_H
