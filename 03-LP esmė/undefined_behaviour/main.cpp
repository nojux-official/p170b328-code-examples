#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void process(int* c);

int main() {
    int a = 0;
    int* c = &a;
    vector<thread> threads;
    threads.reserve(15);
    for (int i = 0; i < 15; i++){
        threads.emplace_back(process, c);
    }
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
    cout << *c << endl;
    return 0;
}

void process(int* c){
    int k = 0;
    for (int i = 0; i < 10; i++){
        k = *c;
        k++;
        *c = k;
    }
}
