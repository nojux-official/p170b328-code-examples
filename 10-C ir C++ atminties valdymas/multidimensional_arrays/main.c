#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_2d_matrix_with_numbers(long** matrix1, size_t width, size_t height);
long** double_matrix(long** source, size_t width, size_t height, long** result);
void print_matrix(int WIDTH, int HEIGHT, long *const *result);

int main() {
    const int WIDTH = 50;
    const int HEIGHT = 40;
    long** matrix1 = malloc(sizeof(long*) * HEIGHT);
    for (size_t i = 0; i < HEIGHT; i++) {
        matrix1[i] = malloc(sizeof(long) * WIDTH);
    }
    fill_2d_matrix_with_numbers(matrix1, WIDTH, HEIGHT);
    long** result = malloc(sizeof(long*) * HEIGHT);
    for (size_t i = 0; i < HEIGHT; i++) {
        result[i] = malloc(sizeof(long) * WIDTH);
    }
    double_matrix(matrix1, WIDTH, HEIGHT, result);
    print_matrix(WIDTH, HEIGHT, result);
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

void fill_2d_matrix_with_numbers(long **matrix1, size_t width, size_t height) {
    srandom(time(NULL));
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            matrix1[i][j] = random() / 200;
        }
    }
}

long **double_matrix(long **source, size_t width, size_t height, long** result) {
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            result[i][j] = source[i][j] * 2;
        }
    }
    return result;
}
