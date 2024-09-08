#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <ranges>

using namespace std;

/// Writes some simple output to console output
/// \param name - thread's name, printed in each output line
void execute(const string &name);

int main() {
    // create names for threads
    vector<string> names = {"First", "Second"};
    // create a view that will hold threads - one thread per name
    auto threads = names
                   | views::transform([](auto& name) {
                       return thread(execute, name);
                   });
    // wait for each thread to finish
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
    cout << "Program finished execution" << endl;
    return 0;
}

void execute(const string &name) {
    cout << name << ": one" << endl;
    cout << name << ": two" << endl;
    cout << name << ": three" << endl;
}
