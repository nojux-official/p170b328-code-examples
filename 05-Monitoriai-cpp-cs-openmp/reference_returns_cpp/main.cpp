#include <iostream>
#include <numeric>
#include <algorithm>
#include <random>
#include <thread>
#include "SortedThreadSafeList.h"

using namespace std;

void insert(SortedThreadSafeList<int> &list);

/// A program that demonstrates the issue with returning data from monitor to a non-synchronized context
int main() {
    SortedThreadSafeList<int> thread_safe_list;  // monitor object, has thread_safe_list inside
    auto storage = thread_safe_list.get_storage();  // get internal list from monitor
    thread thread(insert, ref(thread_safe_list));  // thread object
    // modify the list without synchronization - code does the same as monitor's add(), but without locks
    for (auto i = 10000; i < 15000; i++) {
        if (storage->empty()) {
            storage->push_back(i);
            continue;
        }
        auto current = storage->begin();
        while (i > *current && current < storage->end()) {
            current++;
        }
        storage->insert(current, i);
    }
    thread.join();
    for_each(storage->begin(), storage->end(), [](auto item) { cout << item << endl; });
}

void insert(SortedThreadSafeList<int> &list) {
    vector<int> items(10000);
    iota(items.begin(), items.end(), 0);
    random_device rd;
    default_random_engine engine(rd());
    shuffle(items.begin(), items.end(), engine);
    for_each(items.begin(), items.end(), [&](auto item) { list.add(item); });
}
