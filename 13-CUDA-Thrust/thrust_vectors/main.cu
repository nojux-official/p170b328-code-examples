#include <iostream>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <random>

using namespace std;
using namespace thrust;

const int VECTOR_SIZE = 10;

host_vector<int> get_random_host_vector(size_t size);

int main() {
    host_vector<int> v1 = get_random_host_vector(VECTOR_SIZE);
    cout << "host vector v1 contains:" << endl;
    for_each(v1.begin(), v1.end(), [] (int item) { cout << item << " ";});
    cout << endl;
    host_vector<int> v2 = get_random_host_vector(VECTOR_SIZE);
    cout << "host vector v2 contains:" << endl;
    for_each(v2.begin(), v2.end(), [] (int item) { cout << item << " ";});
    cout << endl;
    device_vector<int> dv1 = v1;
    device_vector<int> dv2 = v2;
    device_vector<int> dv_res(VECTOR_SIZE);
    for (int i = 0; i < dv_res.size(); i++) {
        dv_res[i] = dv1[i] + dv2[i];
    }
    host_vector<int> res = dv_res;
    cout << "host vector res contains:" << endl;
    for_each(res.begin(), res.end(), [] (int item) { cout << item << " ";});
    cout << endl;
    return 0;
}

host_vector<int> get_random_host_vector(size_t size) {
    host_vector<int> random_vector(size);
    random_device dev;
    default_random_engine engine(dev());
    uniform_int_distribution<int> uniform_dist(0, 100);
    generate(random_vector.begin(), random_vector.end(), [&] { return uniform_dist(engine); });
    return random_vector;
}