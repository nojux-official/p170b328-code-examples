#include <complex>
#include <vector>
#include <fstream>
#include <chrono>
#include <iostream>
#include "TinyPngOut.hpp"

using namespace std;
using namespace std::chrono;

bool is_mandelbrot(complex<double> number, int iterations);

double compute_row(int col);

double compute_column(int row);

const double WIDTH = 2.5;
const double HEIGHT = 2.5;
const size_t ROWS = 2000;
const size_t COLS = 2000;

// generates an image of Mandelbrot set
int main() {
    // buffer for the image data. Each pixel is 3 bytes (red, green, blue)
    auto *png_buffer = new uint8_t[ROWS * COLS * 3];
    auto start = high_resolution_clock::now();  // start time measurement
#pragma omp parallel for default(none) shared(png_buffer, COLS)
    // iterate over all columns and rows
    for (auto col = 0; col < COLS; col++) {
        for (auto row = 0; row < ROWS; row++) {
            // if coordinates converge to 0, mark the pixel black (0), white otherwise (255)
            auto x = compute_row(row);
            auto y = compute_column(col);
            complex<double> c(x, y);
            auto colour = is_mandelbrot(c, 100) ? 0 : 255;
            auto offset = (col * COLS * 3) + (3 * row);
            png_buffer[offset] = colour;
            png_buffer[offset + 1] = colour;
            png_buffer[offset + 2] = colour;
        }
    }
    auto stop = high_resolution_clock::now();
    // output image
    ofstream out("mandelbrot.png", std::ios::binary);
    TinyPngOut png_out(COLS, ROWS, out);
    png_out.write(png_buffer, COLS * ROWS);
    // release memory
    delete[] png_buffer;
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Image generated in " << duration.count() << " ms" << endl;
}

double compute_row(int col) {
    const complex<double> CENTER(-0.75, 0.0);
    return CENTER.real() - WIDTH / 2.0 + (double) col * WIDTH / (double) COLS;
}

bool is_mandelbrot(complex<double> number, int iterations) {
    complex<double> z(0.0, 0.0);
    auto accumulator = 0;
    while (accumulator < iterations && abs(z) < 2.0) {
        z = z * z + number;
        accumulator++;
    }
    return accumulator == iterations;
}

double compute_column(int row) {
    const complex<double> CENTER(-0.75, 0.0);
    return CENTER.imag() - HEIGHT / 2.0 + (double) row * HEIGHT / (double) ROWS;
}
