#include <iostream>
#include <vector>
#include <numeric>
#include <future>

using namespace std;

int get_sum(vector<int>& values);

int main() {
    vector<int> firstDataSet;
    firstDataSet.resize(10000);
    fill(firstDataSet.begin(), firstDataSet.end(), 1);
    vector<int> secondDataSet;
    secondDataSet.resize(8000);
    fill(secondDataSet.begin(), secondDataSet.end(), 2);
    auto future = async(launch::async, get_sum, ref(firstDataSet));
    auto first_sum = get_sum(secondDataSet);
    auto full_sum = first_sum + future.get();
    cout << full_sum << endl;
    return 0;
}

int get_sum(vector<int>& values) {
    return accumulate(values.begin(), values.end(), 0, [](const int& x, const int& y) {
        return x + y;
    });
}
