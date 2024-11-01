#include <iostream>
#include <vector>
#include <algorithm>
#include "Animal.h"

using namespace std;

Animal* get_chinchilla(const string& name);
Animal& get_chicken(const string& name);

int main() {
    const auto chinchilla = get_chinchilla("Django");
    auto chicken = get_chicken("Rosetta");
    const auto cow = new Animal("Belle", "cow");
    auto sheep = Animal("Dolly", "sheep");
    vector animals = {chinchilla, &chicken, cow, &sheep};
    for_each(animals.begin(), animals.end(), [](auto* animal) {
        cout << animal->get_species() << " named " << animal->get_name() << endl;
    });
    delete chinchilla;
    delete cow;
    return 0;
}

Animal* get_chinchilla(const string& name) {
    return new Animal(name, "chinchilla");
}

Animal& get_chicken(const string &name) {
    const auto animal = new Animal(name, "chicken");
    return *animal;
}
