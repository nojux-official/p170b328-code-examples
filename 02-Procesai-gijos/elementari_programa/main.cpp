#include <thread>
#include <iostream>
#include <string>

using namespace std;

/// Writes some simple output to console output
/// \param name - thread's name, printed in each output line
void execute(const string& name);

int main(){
    // create names for threads
    string name1("Pirma");
    string name2("Antra");
    // launch execute(name1) in a new thread
    thread thread1(execute, name1);
    // launch execute(name2) in a new thread
    thread thread2(execute, name2);
    // wait for thread1 to finish
    thread1.join();
    // wait for thread2 to finish
    thread2.join();
    cout << "Programa baigė darbą" << endl;
    return 0;
}

void execute(const string& name){
    cout << name << ": vienas" << endl;
    cout << name << ": du" << endl;
    cout << name << ": trys" << endl;
}
