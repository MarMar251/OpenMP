#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

#define R_MAX 1.5
#define R_MIN -2.0
#define I_MAX 1.0
#define I_MIN -1.0
#define MAX_ITER 8000
#define NUM_POINTS 10000000 // Number of random points to test

int is_in_mandelbrot(double x0, double y0) {
    double x = 0, y = 0, x2 = 0, y2 = 0;
    int iteration = 0;

    while (x2 + y2 <= 4 && iteration < MAX_ITER) {
        y = 2 * x * y + y0;
        x = x2 - y2 + x0;
        x2 = x * x;
        y2 = y * y;
        iteration++;
    }

    return iteration == MAX_ITER;
}

int main() {
    srand(time(0)); // Seed for random number generation
    int in_set = 0;
    double area_estimate;
    double total_area = (R_MAX - R_MIN) * (I_MAX - I_MIN);

    // Sequential calculation
    double start_time = omp_get_wtime();
    for (int i = 0; i < NUM_POINTS; i++) {
        double real = R_MIN + ((double)rand() / RAND_MAX) * (R_MAX - R_MIN);
        double imag = I_MIN + ((double)rand() / RAND_MAX) * (I_MAX - I_MIN);

        if (is_in_mandelbrot(real, imag)) {
            in_set++;
        }
    }
    area_estimate = total_area * in_set / NUM_POINTS;
    double sequential_time = omp_get_wtime() - start_time;
    printf("Sequential Mandelbrot Set Area Estimate: %f\n", area_estimate);
    printf("Sequential Time: %f seconds\n\n", sequential_time);

    // Testing parallel calculation with various numbers of threads
    for (int num_threads = 1; num_threads <= 8; num_threads *= 2) {
        in_set = 0;
        omp_set_num_threads(num_threads);

        start_time = omp_get_wtime();
        #pragma omp parallel for reduction(+:in_set)
        for (int i = 0; i < NUM_POINTS; i++) {
            double real = R_MIN + ((double)rand() / RAND_MAX) * (R_MAX - R_MIN);
            double imag = I_MIN + ((double)rand() / RAND_MAX) * (I_MAX - I_MIN);

            if (is_in_mandelbrot(real, imag)) {
                in_set++;
            }
        }
        area_estimate = total_area * in_set / NUM_POINTS;
        double parallel_time = omp_get_wtime() - start_time;
        double speedup = sequential_time / parallel_time;

        printf("Threads: %d\n", num_threads);
        printf("Parallel Mandelbrot Set Area Estimate: %f\n", area_estimate);
        printf("Parallel Time: %f seconds\n", parallel_time);
        printf("Speedup: %f\n\n", speedup);
    }

    return 0;
}