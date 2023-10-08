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
    // modify the list without synchronization - adds items to the beginning of the vector, but without locks
    for (auto i = 10000; i < 15000; i++) {
        // this is a bad thing to do, crashes with "double free or corruption (!prev)" since two threads
        storage->insert(storage->begin(), i);
    }
    thread.join();
    // print items to the console
    for_each(storage->begin(), storage->end(), [](auto item) { cout << item << endl; });
}


/// Inserts a large number of items into a thread-safe-list using its add method
/// \param list
void insert(SortedThreadSafeList<int> &list) {
    // create a vector of 10000 items
    vector<int> items(10000);
    // fill the array with numbers from 0 to 10000
    iota(items.begin(), items.end(), 0);
    // shuffle the items
    random_device rd;
    default_random_engine engine(rd());
    shuffle(items.begin(), items.end(), engine);
    // add each item to the list
    for_each(items.begin(), items.end(), [&](auto item) { list.add(item); });
}
