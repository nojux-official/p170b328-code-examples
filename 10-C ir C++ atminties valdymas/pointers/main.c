#include <stdio.h>

int multiply_by_two(int number);
void multiply_by_two_in_place(int* number);

/// An example program that does not do anything meaningful and demonstrates passing values to functions by value and by
/// pointer
int main() {
    int number = 42;
    // number is a regular integer - it will print 42
    printf("Number is %d\n", number);
    // get address of number and store it in number_ptr variable
    int* number_ptr = &number;
    // this will print an address because we pass a pointer (something like 0x7ffe3417262c)
    printf("Address of number is %p\n", number_ptr);
    // this will print 42, because we are dereferencing a pointer (getting value in that memory location)
    printf("Dereferenced number_ptr is %d\n", *number_ptr);
    // number is passed by making a copy of number - any modifications inside the function are made on a copy
    printf("Doubled number is %d\n", multiply_by_two(number));
    // a copy is also made here - number_ptr is deferenced, a copy of that value is made and the function works on a
    // copy
    printf("Doubled number is %d\n", multiply_by_two(*number_ptr));
    // address of number is passed - the function knows a memory location and can update it
    multiply_by_two_in_place(&number);
    printf("Doubled in place: %d\n", number);
    // number_ptr is the same as &number, so the same happens again
    multiply_by_two_in_place(number_ptr);
    printf("Doubled in place again: %d\n", number);
    return 0;
}

/// Computes the number multiplied by two. Accepts int as parameter, which means that a copy of the integer is made and
/// we work with a copy inside this function
/// \param number number to be multiplied
/// \return a new number
int multiply_by_two(const int number){
    return number * 2;
}

/// Modifies the number to hold the previous value multiplied by two. int* is passed which is a memory address - we can
/// write to this memory if we like
/// \param number address of number to be modified
void multiply_by_two_in_place(int* number) {
    *number = *number * 2;
}