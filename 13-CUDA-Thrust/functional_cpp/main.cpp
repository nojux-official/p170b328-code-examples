#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

vector<int> get_vector();

int main() {
    auto data_vector = get_vector();
    vector<int> filtered_vector(data_vector.size());
    // filter only even numbers
    copy_if(data_vector.begin(), data_vector.end(), filtered_vector.begin(),
            [](int item){ return item % 2 == 0;});
    vector<int> squared_vector(filtered_vector.size());
    // map to squares
    transform(filtered_vector.begin(), filtered_vector.end(), squared_vector.begin(),
            [](int item) { return item * item;});
    // reduce to sum
    int sum = accumulate(squared_vector.begin(), squared_vector.end(), 0,
            [](int accumulator, int operand){ return accumulator + operand;});
    cout << sum << endl;
}

vector<int> get_vector() {
    vector<int> result;
    result.reserve(20);
    for (auto i = 1; i < 21; i++) {
        result.push_back(i);
    }
    return result;
}