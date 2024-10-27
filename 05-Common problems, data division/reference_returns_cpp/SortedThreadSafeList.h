//
// Created by ryselis on 2021-08-15.
//

#ifndef REFERENCE_RETURNS_CPP_SORTEDTHREADSAFELIST_H
#define REFERENCE_RETURNS_CPP_SORTEDTHREADSAFELIST_H

#include <vector>
#include <mutex>

using namespace std;

template<typename T>
class SortedThreadSafeList {
    vector<T> storage;
    mutex m;
public:
    /// Adds an item to the storage so that it remains sorted in a thread-safe way
    /// \param item - an item to add
    void add(T item) {
        unique_lock locker(m);
        if (storage.empty()) {  // if storage is empty, there is only one way to add an item
            storage.push_back(item);
            return;
        }
        auto current = storage.begin();
        while (item > *current && current < storage.end()) {
            ++current;
        }
        storage.insert(current, item);
    }
    /// Returns the internal storage object
    vector<T>* get_storage() {
        unique_lock locker(m);
        return &storage;
    }
};


#endif //REFERENCE_RETURNS_CPP_SORTEDTHREADSAFELIST_H
