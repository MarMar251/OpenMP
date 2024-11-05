#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double f(double x) {
    return log(x) / x;
}

int main(int argc, char* argv[]) {
    const double a = 1.0;    // Start of interval
    const double b = 10.0;   // End of interval
    const int n = 1000000;   // Number of subdivisions
    const double dx = (b - a) / n; // Width of each subdivision

    double total_area = 0.0;
    int num_threads = 1;  // Default to 1 thread if not specified

    // If a thread count is provided as a command-line argument, use it
    if (argc > 1) {
        num_threads = atoi(argv[1]);
    }
    omp_set_num_threads(num_threads);

    // Start timing
    double start_time = omp_get_wtime();

    // Parallel region to compute the area
    #pragma omp parallel
    {
        double partial_sum = 0.0;

        #pragma omp for
        for (int i = 0; i < n; i++) {
            double x = a + i * dx;
            partial_sum += f(x) * dx;
        }

        // Accumulate results in the main thread
        #pragma omp critical
        total_area += partial_sum;
    }

    // End timing
    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    // Output results
    printf("The integral approximation is: %.8f\n", total_area);
    printf("Number of threads used: %d\n", num_threads);
    printf("Execution time: %.8f seconds\n", elapsed_time);

    return 0;
}