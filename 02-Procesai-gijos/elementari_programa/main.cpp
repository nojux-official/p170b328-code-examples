#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

/// Writes some simple output to console output
/// \param name - thread's name, printed in each output line
void execute(const string& name);

int main(){
    // create names for threads
    vector<string> names = {"First", "Second"};
    // create a vector that will hold threads
    vector<thread> threads;
    threads.reserve(names.size());
    thread t = move(threads[0]);
    // for each name create a thread. Created thread is immediately launched
    for(auto& name: names) {
        // emplace_back automatically creates thread object passing all arguments to its constructor
        threads.emplace_back(execute, name);
    }
    // wait for each thread to finish
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
    cout << "Program finished execution" << endl;
    return 0;
}

void execute(const string& name){
    cout << name << ": one" << endl;
    cout << name << ": two" << endl;
    cout << name << ": three" << endl;
}
