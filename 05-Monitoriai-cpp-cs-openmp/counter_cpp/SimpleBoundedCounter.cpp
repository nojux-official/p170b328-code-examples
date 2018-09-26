#include <iostream>
#include "SimpleBoundedCounter.h"

SimpleBoundedCounter::SimpleBoundedCounter() {
    count = SimpleBoundedCounter::MIN;
}

void SimpleBoundedCounter::setCount(long newValue) {
    count = newValue;
    cv.notify_all();
}

void SimpleBoundedCounter::increase() {
    unique_lock<mutex> guard(lock);
    cv.wait(guard, [=]{ return count < SimpleBoundedCounter::MAX;});
    setCount(count + 1);
}

void SimpleBoundedCounter::decrease() {
    unique_lock<mutex> guard(lock);
    cv.wait(guard, [=]{ return count > 0;});
    setCount(count - 1);
}

long SimpleBoundedCounter::getCount() {
    return count;
}
