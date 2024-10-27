#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>

using namespace std;

constexpr int VECTOR_SIZE = 100000000;

int main() {
    // create 2 vectors
    vector<int> vector1(VECTOR_SIZE);
    vector<int> vector2(VECTOR_SIZE);
    // generate some data
    iota(vector1.begin(), vector1.end(), 0);
    iota(vector2.begin(), vector2.end(), 0);
    // create vector for the sum of vector1 and vector2
    vector<int> vector3(VECTOR_SIZE);
    const auto t1 = chrono::high_resolution_clock::now();
    // parallel for makes the for loop run in parallel
    // default(none) means that for all variables used inside parallel for block we have to define if they are private
    // or shared
    // shared means that all our vectors are shared between threads (vectors are not copied for each thread)
#pragma omp parallel for default(none) shared(vector1, vector2, vector3, VECTOR_SIZE)
    for (auto i = 0; i < VECTOR_SIZE; i++) {
        // compute sum for each item
        vector3[i] = vector1[i] + vector2[i];
    }
    const auto t2 = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() << endl;
}
