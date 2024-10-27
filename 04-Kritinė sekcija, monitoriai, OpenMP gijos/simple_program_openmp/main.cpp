#include <string>
#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

void execute(const string &name);

/// The program spawns two threads that run concurrently by executing the same code that prints some output to the
/// console, but the printing is thread-safe.
int main() {
    // construct a vector of strings
    const vector<string> thread_names = {"First", "Second"};
    // set the amount of threads to be equal to the size of the vector. This is a bad idea if the vector is large.
    // static case is recommended here because thread_names.size() returns size_t, which is unsigned, but
    // omp_set_num_threads expects an int (signed). Static cast converts the value safely.
    omp_set_num_threads(static_cast<int>(thread_names.size()));
    // start a parallel region. This region will run twice in two different threads. We also state that thread_names
    // variable is shared, i.e., both threads will get the original vector
#pragma omp parallel shared(thread_names) default(none)
    {
        // thread number is different for each thread, retrieve it
        const auto threadNumber = omp_get_thread_num();
        // get the name from the correct index in the array
        const auto& name = thread_names[threadNumber];
        // the following code is in a critical section
#pragma omp critical
        {
            execute(name);
        }
    }
    // this line will be printed when all threads in a parallel region are finished
    cout << "Program finished execution" << endl;
}

void execute(const string &name) {
    cout << name << ": one" << endl;
    cout << name << ": two" << endl;
    cout << name << ": three" << endl;
}