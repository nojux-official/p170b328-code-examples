#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    const auto MIN = 0;
    const auto MAX = 50;
    auto count = 0;
    const auto increasing_thread_count = 10;
    const auto decreasing_thread_count = 9;
    const auto total_threads = increasing_thread_count + decreasing_thread_count;
#pragma omp parallel num_threads(total_threads) default(none) shared(increasing_thread_count, count)
    {
        int thread_id = omp_get_thread_num();
        if (thread_id < increasing_thread_count) {
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
                    if (count > MIN) {
                        count--;
                        i++;
                    }
                }
            }
        }
    }
    cout << count << endl;
}