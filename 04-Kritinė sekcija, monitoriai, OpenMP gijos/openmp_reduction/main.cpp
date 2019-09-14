#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    auto c = 0;
    auto thread_count = 50;
    auto k = 5;
#pragma omp parallel reduction(+:c) num_threads(thread_count)
    {
        for (int i = 0; i < k; i++){
            c += i;
        }
    }
    cout << c << endl;
}