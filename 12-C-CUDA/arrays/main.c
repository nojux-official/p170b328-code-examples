#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_array_with_random_numbers(int* array, size_t array_size);
int sum(const int* array, size_t array_size);
void copy_array(const int* from, int* to, size_t array_size);

int main() {
    srand((unsigned int) time(NULL));
    unsigned int n = (unsigned int) (rand() % 1000);
    int array1[n];
    fill_array_with_random_numbers(array1, n);
    int* array2 = malloc(n * sizeof(int));
    copy_array(array1, array2, n);
    int sum1 = sum(array1, n);
    int sum2 = sum(array2, n);
    free(array2);
    printf("Sum is %d\n", sum1);
    printf("Sum is %d", sum2);
    return 0;
}

int sum(const int *array, size_t array_size) {
    int result = 0;
    for (int i = 0; i < array_size; i++) {
        result += array[i];
    }
    return result;
}

void fill_array_with_random_numbers(int *array, size_t array_size) {
    srand((unsigned int) time(NULL));
    for (int i = 0; i < array_size; i++) {
        array[i] = rand() % 100;
    }
}

void copy_array(const int *from, int *to, size_t array_size) {
    for (int i = 0; i < array_size; i++) {
        to[i] = from[i];
    }
}
