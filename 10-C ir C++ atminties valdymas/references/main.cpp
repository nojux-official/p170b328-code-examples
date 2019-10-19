#include <iostream>
#include "Counter.h"

void decrease_counter_ref(Counter& counter);

void decrease_counter_copy(Counter counter);
void decrease_counter_pointer(Counter* counter);

using namespace std;

int main() {
    Counter counter;
    cout << "Initial value: " <<  counter.get_count() << endl;
    counter.increase();
    cout << "After increase in same function: " << counter.get_count() << endl;
    decrease_counter_ref(counter);
    cout << "After decrease when passed by reference: " << counter.get_count() << endl;
    decrease_counter_copy(counter);
    cout << "After decrease when passed by value: " << counter.get_count() << endl;
    decrease_counter_pointer(&counter);
    cout << "After decrease when passed as pointer: " << counter.get_count() << endl;
    return 0;
}

void decrease_counter_ref(Counter &counter) {
    counter.decrease();
}

void decrease_counter_copy(Counter counter) {
    counter.decrease();
}

void decrease_counter_pointer(Counter *counter) {
    counter->decrease();
}
