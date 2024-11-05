#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double f(double x) {
    return log(x) / x; 
}

int main(int argc, char* argv[]) {
    const double start_interval = 1.0;
    const double end_interval = 10.0;
    const int subdivisions = 1000000;
    const double Width = (end_interval - start_interval) / subdivisions;

    double total_area;      
    double sequential_time; 

    // Calculate the area sequentially for speedup comparison
    total_area = 0.0;
    double start_time = omp_get_wtime();
    for (int i = 0; i < subdivisions; i++) {
        double x = start_interval + i * Width;
        total_area += f(x) * Width;
    }
    sequential_time = omp_get_wtime() - start_time;

    // Testing parallel calculation with various numbers of threads
    for (int num_threads = 1; num_threads <= 8; num_threads *= 2) {
        total_area = 0.0;  // Reset total area for each thread count
        omp_set_num_threads(num_threads);  // Set number of threads

        start_time = omp_get_wtime();  // Start timing

        // Parallel region to compute the area
        #pragma omp parallel
        {
            double partial_sum = 0.0;

            #pragma omp for
            for (int i = 0; i < subdivisions; i++) {
                double x = start_interval + i * Width;
                partial_sum += f(x) * Width;
            }

            // Accumulate results in the main thread
            #pragma omp critical
            total_area += partial_sum;
        }

        // End timing
        double end_time = omp_get_wtime();
        double elapsed_time = end_time - start_time;
        
        // Calculate speedup
        double speedup = sequential_time / elapsed_time;

        // Output results
        printf("Threads: %d\n", num_threads);
        printf("Area Estimate: %.8f\n", total_area);
        printf("Execution Time: %.8f seconds\n", elapsed_time);
        printf("Speedup: %.2f\n\n", speedup);
    }

    return 0;
}