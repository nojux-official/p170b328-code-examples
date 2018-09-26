#include <iostream>
#include <omp.h>
#include <mutex>
#include <condition_variable>

using namespace std;

int main() {
    const auto MIN = 0;
    const auto MAX = 50;
    auto count = 0;
    auto increaser_count = 10;
    auto decreaser_count = 9;
#pragma omp parallel num_threads(increaser_count + decreaser_count)
    {
        int thread_id = omp_get_thread_num();
        if (thread_id < increaser_count) {
            for (auto i = 0; i < 50;) {
#pragma omp critical (count_critical)
                {
                    if (count < MAX) {
                        count++;
                        i++;
                    }
                }
            }
        } else {
            for (auto i = 0; i < 50;) {
#pragma omp critical (count_critical)
                {
                    if (count > 0) {
                        count--;
                        i++;
                    }
                }
            }
        }
    }
    cout << count << endl;
}