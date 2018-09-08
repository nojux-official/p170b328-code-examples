#include <thread>
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <cmath>

using namespace std;

int main() {
    // generate some data
    const int DATA_SIZE = 9999;
    vector<int> data;
    data.reserve(DATA_SIZE);
    for (int i = 0; i < DATA_SIZE; i++){
        data.push_back(i);
    }
    // initialize result vectors
    vector<int> squares;
    squares.resize(DATA_SIZE);
    vector<double> roots;
    roots.resize(DATA_SIZE);
    vector<thread> threads;
    // launch threads calculating squares and square roots
    threads.emplace_back([&](){
        transform(data.begin(), data.end(), squares.begin(), [](int i){ return i*i;});
    });
    threads.emplace_back([&](){
        transform(data.begin(), data.end(), roots.begin(), (double(*)(double)) sqrt);
    });
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
    // print result to console
    for (int i : squares) {
        cout << i << endl;
    }
    for (auto i: roots){
        cout << i << endl;
    }
    return 0;
}
