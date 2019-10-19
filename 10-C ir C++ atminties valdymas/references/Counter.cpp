//
// Created by ryselis on 2019-10-16.
//

#include "Counter.h"

void Counter::increase() {
    count++;
}

void Counter::decrease() {
    count--;
}

int Counter::get_count() {
    return count;
}
