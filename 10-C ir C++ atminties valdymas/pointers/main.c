#include <stdio.h>

int multiply_by_two(int number);
void multiply_by_two_in_place(int* number);

int main() {
    int number = 42;
    printf("Number is %d\n", number);
    int* number_ptr = &number;
    printf("Address of number is %p\n", number_ptr);
    printf("Deferenced number_ptr is %d\n", *number_ptr);
    printf("Doubled number is %d\n", multiply_by_two(number));
    printf("Doubled number is %d\n", multiply_by_two(*number_ptr));
    multiply_by_two_in_place(&number);
    printf("Doubled in place: %d\n", number);
    multiply_by_two_in_place(number_ptr);
    printf("Doubled in place again: %d\n", number);
    return 0;
}

int multiply_by_two(int number){
    return number * 2;
}

void multiply_by_two_in_place(int* number) {
    *number = *number * 2;
}