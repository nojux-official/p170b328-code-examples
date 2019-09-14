#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    auto c = 99;
    auto * lock = new omp_lock_t;
    omp_init_lock(lock);
#pragma omp parallel num_threads(3) private(c)
    {
        c = omp_get_thread_num();
        omp_set_lock(lock);
        cout << "in thread: " << c << endl;
        omp_unset_lock(lock);
    }
    cout << "after parallel: " << c << endl;
    omp_destroy_lock(lock);
    return 0;
}