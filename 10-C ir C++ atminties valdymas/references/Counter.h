//
// Created by ryselis on 2019-10-16.
//

#ifndef REFERENCES_COUNTER_H
#define REFERENCES_COUNTER_H


class Counter {
private:
    int count = 0;
public:
    void increase();
    void decrease();
    int get_count();
};


#endif //REFERENCES_COUNTER_H
