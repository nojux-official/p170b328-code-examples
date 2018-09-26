#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>
#include "SimpleBoundedCounter.h"

using namespace std;

int main() {
    vector<thread> threads;
    SimpleBoundedCounter counter;
    threads.reserve(19);
    for (int i = 0; i < 10; i++){
        threads.emplace_back([&]{
            for (int j = 0; j < 50; j++) {
                counter.increase();
            }
        });
    }
    for (int i = 0; i < 9; i++) {
        threads.emplace_back([&]{
            for (int j = 0; j < 50; j++) {
                counter.decrease();
            }
        });
    }
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
    cout << counter.getCount() << endl;
    return 0;
}