#include <iostream>
#include <vector>
#include <algorithm>
#include "Animal.h"

using namespace std;

Animal* get_chinchilla(const string& name);
Animal& get_chicken(const string& name);

int main() {
    auto chinchilla = get_chinchilla("Django");
    auto chicken = get_chicken("Rosetta");
    auto cow = new Animal("Belle", "cow");
    auto sheep = Animal("Dolly", "sheep");
    vector<Animal*> animals = {chinchilla, &chicken, cow, &sheep};
    for_each(animals.begin(), animals.end(), [](Animal* animal) {
        cout << animal->get_species() << " named " << animal->get_name() << endl;
    });
    delete(chinchilla);
    delete(cow);
    return 0;
}

Animal* get_chinchilla(const string& name) {
    auto animal = new Animal(name, "chinchilla");
    return animal;
}

Animal& get_chicken(const string &name) {
    auto animal = new Animal(name, "chicken");
    return *animal;
}
