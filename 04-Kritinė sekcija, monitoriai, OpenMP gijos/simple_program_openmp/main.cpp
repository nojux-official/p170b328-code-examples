#include <string>
#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

void execute(const string &name);

int main() {
    vector<string> thread_names = {"First", "Second"};
    omp_set_num_threads((int) thread_names.size());
#pragma omp parallel shared(thread_names) default(none)
    {
        auto threadNumber = omp_get_thread_num();
        string name = thread_names[threadNumber];
#pragma omp critical
        {
            execute(name);
        }
    }
    cout << "Program finished execution" << endl;
}

void execute(const string &name) {
    cout << name << ": one" << endl;
    cout << name << ": two" << endl;
    cout << name << ": three" << endl;
}