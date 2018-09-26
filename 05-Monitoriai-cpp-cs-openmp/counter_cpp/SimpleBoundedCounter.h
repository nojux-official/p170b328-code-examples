#ifndef COUNTER_CPP_SIMPLEBOUNDEDCOUNTER_H
#define COUNTER_CPP_SIMPLEBOUNDEDCOUNTER_H


#include <mutex>
#include <condition_variable>

using namespace std;

class SimpleBoundedCounter {
private:
    static const long MIN = 0;
    static const long MAX = 50;
    long count;
    mutex lock;
    condition_variable cv;
    void setCount(long newValue);
public:
    SimpleBoundedCounter();
    void increase();
    void decrease();
    long getCount();
};


#endif //COUNTER_CPP_SIMPLEBOUNDEDCOUNTER_H
