#include <iostream>
#include <thread>
#include <vector>
#include <functional>

using namespace std;

void process(int* c);

/**
 * This program demonstrates a bad programming example - running it will produce different output each time! 
 */

const size_t THREAD_COUNT = 15;

int main() {
    auto a = 0;  // create a variable with some initial value assigned
    auto c = &a;  // get a pointer to that variable
    // we are going to launch 15 threads - make a vector with 15 slots available
    vector<thread> threads;
    threads.reserve(THREAD_COUNT);
    for (auto i = 0; i < THREAD_COUNT; i++){
        // launch 15 processes passing the same pointer c
        threads.emplace_back(process, c);
    }
    // wait for all threads to finish
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
    // output the value of what we got
    cout << *c << endl;
    return 0;
}

/// Function that takes a value pointed by c, and writes that value increased by 1 back to c.
/// Does this 1000 times.
/// \param c pointer to shared memory across threads
void process(int* c){
    for (int i = 0; i < 1000; i++){
        auto k = *c;  // take value that is currently in memory location c
        k++; // increment k; *c stays the same, only k is incremented
        // another thread may have read the same value of k, resulting in two threads writing the
        // same value (race condition).
        // we will anyway write whatever k holds back to *c.
        *c = k;
    }
}
