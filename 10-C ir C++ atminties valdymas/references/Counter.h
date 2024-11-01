//
// Created by ryselis on 2019-10-16.
//

#ifndef REFERENCES_COUNTER_H
#define REFERENCES_COUNTER_H


class Counter {
    int count = 0;
public:
    void increase();
    void decrease();
    [[nodiscard]] int get_count() const;
};


#endif //REFERENCES_COUNTER_H
