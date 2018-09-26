#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    auto count = 0;
#pragma omp parallel num_threads(100)
    {
        for (int i = 0; i < 50; i++) {
#pragma omp critical
            {
                count++;
            };
        }
#pragma omp barrier
#pragma omp master
        {
            cout << count << endl;
        }
#pragma omp barrier
        for (int i = 0; i < 50; i++) {
#pragma omp critical
            {
                count++;
            };
        }
    }
    cout << count << endl;
}