//
// Created by ryselis on 2019-09-15.
//

#ifndef POINTER_STEALING_THREADSAFESTACK_H
#define POINTER_STEALING_THREADSAFESTACK_H

#include <stack>
#include <mutex>

using namespace std;

template <class T>
class ThreadSafeStack {
private:
    stack<T> storage;
    mutex m;
public:
    void push(T item) {
        unique_lock<mutex> lock(m);
        storage.push(item);
    }
    template <typename Function>
    void call_user_function(Function func) {
        unique_lock<mutex> lock(m);
        func(storage);
    };
};


#endif //POINTER_STEALING_THREADSAFESTACK_H
