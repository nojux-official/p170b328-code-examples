#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    auto c = 99;
    omp_lock_t lock;
    omp_init_lock(&lock);
#pragma omp parallel for lastprivate(c) default(none) shared(lock, cout)
    for (int i = 0; i < 3; i++){
        c = omp_get_thread_num();
        omp_set_lock(&lock);
        cout << "in thread: " << c << endl;
        omp_unset_lock(&lock);
    }
    cout << "after parallel: " << c << endl;
    omp_destroy_lock(&lock);
    return 0;
}