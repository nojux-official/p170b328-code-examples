#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_2d_matrix_with_numbers(long** matrix1, size_t width, size_t height);
long** double_matrix(long** source, size_t width, size_t height, long** result);
void print_matrix(int WIDTH, int HEIGHT, long *const *result);

/// creates a 2D matrix, fills is with random numbers, multiplies it by 2 and prints the result to console
int main() {
    // matrix dimensions
    const int WIDTH = 50;
    const int HEIGHT = 40;
    // allocate memory for the matrix. matrix1 is an array of matrix rows - each item is a long*. Since matrix1 holds
    // an array of long*, its type is an array of long* - long**
    long** matrix1 = malloc(sizeof(long*) * HEIGHT);
    for (size_t i = 0; i < HEIGHT; i++) {
        matrix1[i] = malloc(sizeof(long) * WIDTH);
    }
    // fill matrix with data
    fill_2d_matrix_with_numbers(matrix1, WIDTH, HEIGHT);
    // allocate memory for the result
    long** result = malloc(sizeof(long*) * HEIGHT);
    for (size_t i = 0; i < HEIGHT; i++) {
        result[i] = malloc(sizeof(long) * WIDTH);
    }
    // multiply matrix by 2
    double_matrix(matrix1, WIDTH, HEIGHT, result);
    // print to console
    print_matrix(WIDTH, HEIGHT, result);
    // free up all memory - one free() for each malloc()
    for (size_t i = 0; i < HEIGHT; i++) {
        free(matrix1[i]);
    }
    free(matrix1);
    for (size_t i = 0; i < HEIGHT; i++) {
        free(result[i]);
    }
    free(result);
    return 0;
}

void print_matrix(const int WIDTH, const int HEIGHT, long *const *result) {
    for (size_t i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%12ld", result[i][j]);
        }
        printf("\n");
    }
}

void fill_2d_matrix_with_numbers(long **matrix1, const size_t width, const size_t height) {
    srandom(time(NULL));
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            matrix1[i][j] = random() / 200;
        }
    }
}

long **double_matrix(long **source, const size_t width, const size_t height, long** result) {
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            result[i][j] = source[i][j] * 2;
        }
    }
    return result;
}
