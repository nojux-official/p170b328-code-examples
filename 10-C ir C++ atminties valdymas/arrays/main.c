#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_array_with_random_numbers(int* array, size_t array_size);
int sum(const int* array, size_t array_size);
void copy_array(const int* from, int* to, size_t array_size);

// a program that calculates sum of two arrays and demonstrates how to use arrays and arrays as pointers
int main() {
    // generate a random array size
    srand((unsigned int) time(NULL));
    unsigned int n = (unsigned int) (rand() % 1000);
    // create an array of selected size. Array is create on stack - if it were larger that main's stack size, we would
    // get a stack overflow. As it is created using array syntax, it is deleted automatically at the end of this function
    int array1[n];
    fill_array_with_random_numbers(array1, n);  // fill array with random numbers
    // create another array of selected size, this time on the heap. Size of this array is only limited by accessible
    // amount of RAM, but it is never deleted automatically - we have to do this manually when we no longer need this
    // array
    int* array2 = malloc(n * sizeof(int));
    // copy content of array1 into array2
    copy_array(array1, array2, n);
    // calculate sum of both arrays - it should be the same. Both arrays were created in different ways (as array and as
    // pointer), but we can just treat them both as pointers.
    int sum1 = sum(array1, n);
    int sum2 = sum(array2, n);
    // array2 no longer needed, we can release the memory
    free(array2);
    printf("Sum is %d\n", sum1);
    printf("Sum is %d", sum2);
    return 0;
}

// calculates the sum of of all elements in array pointed by *array. size is also needed because *array is just memory
// address - we have no idea where is the end of array without the size.
int sum(const int *array, size_t array_size) {
    int result = 0;
    // loop over elements and them together. This is C, so no cool algorithms like accumulate.
    for (size_t i = 0; i < array_size; i++) {
        result += array[i];
    }
    return result;
}

// fills an array with random numbers. Random numbers are generated inside this function.
void fill_array_with_random_numbers(int *array, size_t array_size) {
    srand((unsigned int) time(NULL));
    for (size_t i = 0; i < array_size; i++) {
        array[i] = rand() % 100;
    }
}

// makes a copy of array by iterating over both arrays together and copying elements one by one
void copy_array(const int *from, int *to, size_t array_size) {
    for (size_t i = 0; i < array_size; i++) {
        to[i] = from[i];
    }
}
