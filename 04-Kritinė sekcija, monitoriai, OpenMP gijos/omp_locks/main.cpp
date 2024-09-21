#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    const vector numbers = {1, 5, 8, 10, 15};
    int result = 0;
    omp_lock_t lock;
    omp_init_lock(&lock);
    omp_set_num_threads(static_cast<int>(numbers.size()));
#pragma omp parallel default(none) shared(numbers, lock, result)
    {
        omp_set_lock(&lock);
        const int i = omp_get_thread_num();
        result += numbers[i];
        omp_unset_lock(&lock);
    }
    omp_destroy_lock(&lock);
    cout << result << endl;
    return 0;
}
