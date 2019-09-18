#include <iostream>
#include <list>
#include <algorithm>
#include <random>
#include <thread>

using namespace std;

template<typename T>
void parallel_quick_sort(list<T> input, list<T> &results);

int main() {
    list<int> numbers;
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, 1000); // pseudo random number generator
    for (auto i = 0; i < 33; i++) {
        numbers.push_back(uni(rng));  // uni(rng) will give a new random number between 0 and 1000 each time
    }
    list<int> sorted;  // a list that will contain sorted results
    parallel_quick_sort(numbers, sorted);
    for_each(sorted.begin(), sorted.end(), [](auto item) {cout << item << endl;});
    return 0;
}

template<typename T>
void parallel_quick_sort(list<T> input, list<T> &results) {
    if (input.empty()) {
        // list is empty, nothing to sort
        return;
    }
    // inserts whole content of input into results
    results.splice(results.begin(), input, input.begin());
    // take first element
    T const &pivot = *results.begin();
    // partition modifies input so that all elements matching condition are at the first part of the list, the remainder
    // is at the second part of the list. Returned value is where the split between the two parts is.
    auto divide_point = partition(input.begin(), input.end(), [&](auto &t) { return t < pivot;});
    list<T> lower_part;
    // insert the first part (from beginning to divide point) of input to lower part
    lower_part.splice(lower_part.end(), input, input.begin(), divide_point);
    list<T> new_lower;  // sorted result will be here
    thread t([&]{parallel_quick_sort(lower_part, new_lower);});  // sort in parallel
    // do the same with higher part, but in the same thread. This way we avoid the outrageous number of threads created
    list<T> new_higher;
    parallel_quick_sort(input, new_higher);
    results.splice(results.end(), new_higher);  // add higher part to the end of results
    t.join();  // wait for lower part to finish sorting
    results.splice(results.begin(), new_lower);  // add lower part to the beginning of results
}