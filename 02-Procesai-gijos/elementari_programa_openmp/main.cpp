#include <string>
#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

void execute(const string &vardas);

int main(){
    vector<string> threadNames = {"Pirma", "Antra"};
    omp_set_num_threads(threadNames.size());
    int threadNumber = 0;
    #pragma omp parallel private(threadNumber)
    {
        threadNumber = omp_get_thread_num();
        string name = threadNames[threadNumber];
        execute(name);
    }
    cout << "Programa baigė darbą" << endl;
}

void execute(const string &vardas){
    cout << vardas << ": vienas" << endl;
    cout << vardas << ": du" << endl;
    cout << vardas << ": trys" << endl;
}