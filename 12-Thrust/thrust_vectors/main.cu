#include <iostream>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/iterator/zip_iterator.h>
#include <random>

using namespace std;

constexpr int VECTOR_SIZE = 15;

thrust::host_vector<int> get_random_host_vector(size_t size);

struct add_tuple_values {
    __device__ int operator ()(thrust::tuple<int, int> tuple) {
        return thrust::get<0>(tuple) + thrust::get<1>(tuple);
    }
};

int main() {
    auto v1 = get_random_host_vector(VECTOR_SIZE);
    cout << "host vector v1 contains:" << endl;
    for_each(v1.begin(), v1.end(), [] (int item) { cout << item << " ";});
    cout << endl;
    auto v2 = get_random_host_vector(VECTOR_SIZE);
    cout << "host vector v2 contains:" << endl;
    for_each(v2.begin(), v2.end(), [] (int item) { cout << item << " ";});
    cout << endl;
    thrust::device_vector<int> dv1 = v1;
    thrust::device_vector<int> dv2 = v2;
    thrust::device_vector<int> dv_res(VECTOR_SIZE);
    auto begin = make_zip_iterator(thrust::make_tuple(dv1.begin(), dv2.begin()));
    auto end = make_zip_iterator(thrust::make_tuple(dv1.end(), dv2.end()));
    thrust::transform(begin, end, dv_res.begin(), add_tuple_values());
    thrust::host_vector<int> res = dv_res;
    cout << "host vector res contains:" << endl;
    for_each(res.begin(), res.end(), [] (int item) { cout << item << " ";});
    cout << endl;
    return 0;
}

thrust::host_vector<int> get_random_host_vector(size_t size) {
    thrust::host_vector<int> random_vector(size);
    random_device dev;
    default_random_engine engine(dev());
    uniform_int_distribution<int> uniform_dist(0, 100);
    generate(random_vector.begin(), random_vector.end(), [&] { return uniform_dist(engine); });
    return random_vector;
}
