#include <iostream>
#include <cmath>
#include <future>

using namespace std;

double square_root(double x);

int main() {
    auto task = async(square_root, -1);
    double result;
    try {
        result = task.get();
    } catch (out_of_range& err) {
        cerr << err.what() << endl;
        return 1;
    }
    cout << result << endl;
    return 0;
}

double square_root(double x) {
    if (x < 0) {
        throw out_of_range("x < 0");
    }
    return sqrt(x);
}
