#include <iostream>
#include <list>
#include <future>
#include <random>
#include <algorithm>

using namespace std;

template<typename T>
list<T> parallel_quick_sort(list<T> input);

int main() {
    list<int> numbers;
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, 1000);
    for (auto i = 0; i < 30; i++) {
        numbers.push_back(uni(rng));
    }
    auto sorted = parallel_quick_sort(numbers);
    for_each(sorted.begin(), sorted.end(), [](int item) {cout << item << endl;});
    return 0;
}

template<typename T>
list<T> parallel_quick_sort(list<T> input) {
    if (input.empty()) {
        return input;
    }
    list<T> result;
    result.splice(result.begin(), input, input.begin());
    T const &pivot = *result.begin();
    auto divide_point = partition(input.begin(), input.end(),
                                  [&](T const &t) { return t < pivot; });
    list<T> lower_part;
    lower_part.splice(lower_part.end(), input, input.begin(),
                      divide_point);
    future<list<T> > new_lower(
            async(&parallel_quick_sort<T>, move(lower_part)));
    auto new_higher(
            parallel_quick_sort(move(input)));
    result.splice(result.end(), new_higher);
    result.splice(result.begin(), new_lower.get());
    return result;
}