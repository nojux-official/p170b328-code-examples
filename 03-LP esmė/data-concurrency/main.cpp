#include <thread>
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>

using namespace std;

/// Calculates a square of each element of a portion of data array from start_index to end_index
/// \param data - array to work on
/// \param start_index - the first index to process
/// \param end_index  - the last index to process
void process(int data[], int start_index, int end_index);

int main() {
    // generate some data
    const int DATA_SIZE = 9999;
    int data[DATA_SIZE] = {};
    for (int i = 0; i < DATA_SIZE; i++){
        data[i] = i;
    }
    // determine the number of supported threads
    auto hw_threads = thread::hardware_concurrency(); // might return 0 on some systems
    auto threads_to_use = hw_threads > 0 ? hw_threads : 1;
    // threads will be placed in a vector
    vector<thread> threads;
    threads.reserve(threads_to_use);
    // how many items should be processed in each thread
    int chunk_size = DATA_SIZE / hw_threads;
    // some items may remain unprocessed
    for (int i = 0; i < threads_to_use; i++){
        // last thread should handle the whole remainder of the data
        int end_index = (i == threads_to_use - 1 ? DATA_SIZE - 1: (i+1) * chunk_size - 1);
        // create and launch thread
        thread t(process, data, i * chunk_size, end_index);
        // place thread in a vector using move semantics
        threads.push_back(move(t));
    }
    // wait for all threads to finish
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
    // print result to console
    for (int i : data) {
        cout << i << endl;
    }
    return 0;
}

void process(int data[], int start_index, int end_index){
    for (int i = start_index; i <= end_index; i++){
        data[i] = data[i] * data[i];
    }
}
