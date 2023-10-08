#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <algorithm>
#include "ThreadSafeStack.h"

using namespace std;

/// A program that demonstrates issues with user-defined functions as parameters to synchronized functions
int main() {
    ThreadSafeStack<int> safe_stack;  // thread-safe stack structure
    vector<int> items;
    items.resize(10000);
    // generate items beginning from 0 and going through all vector, incrementing each element by 1. The result is
    // items filled with number from 0 to 1000
    iota(items.begin(), items.end(), 0);
    thread t([&]() {
        // thread that pushes all items on stack
        for_each(items.begin(), items.end(), [&](auto item) {
            safe_stack.push(item);
        });
    });
    // stolen data is going to contain a pointer to internal storage of safe_stack. We can then do something evil without
    // locking a mutex
    stack<int>* stolen_data;
    safe_stack.call_user_function([&](auto& storage) {
        stolen_data = &storage;  // grab a pointer to internal storage of the stack and assign it to our variable
    });
    // do some evil stuff
    for_each(items.begin(), items.end(), [&](auto item) {
        stolen_data->push(item);  // segmentation fault is likely to happen here
    });
    t.join();
}