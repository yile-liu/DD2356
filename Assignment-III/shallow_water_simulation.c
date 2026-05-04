#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 500  // Grid size
#define ITER 20000  // Number of iterations
#define DT 0.01  // Time step
#define DX 1.0   // Grid spacing

double h[N][N], u[N][N], v[N][N];
double h_new[N][N], u_new[N][N], v_new[N][N];
double G = 9.8;

void initialize() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            h[i][j] = 1.0;
            u[i][j] = 0.0;
            v[i][j] = 0.0;
        }
}

void compute() {
    for (int iter = 0; iter < ITER; iter++) {
        #pragma omp parallel for collapse(2) schedule(runtime)
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                double dhdx = (h[i+1][j] - h[i-1][j]) / (2.0 * DX);
                double dhdy = (h[i][j+1] - h[i][j-1]) / (2.0 * DX);
                double dudx = (u[i+1][j] - u[i-1][j]) / (2.0 * DX);
                double dvdy = (v[i][j+1] - v[i][j-1]) / (2.0 * DX);

                h_new[i][j] = h[i][j] - DT * (dudx + dvdy);
                u_new[i][j] = u[i][j] - DT * G * dhdx;
                v_new[i][j] = v[i][j] - DT * G * dhdy;
            }
        }

        #pragma omp parallel for collapse(2) schedule(runtime)
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                h[i][j] = h_new[i][j];
                u[i][j] = u_new[i][j];
                v[i][j] = v_new[i][j];
            }
        }
    }
}

void write_output() {
    FILE *f = fopen("output.txt", "w");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(f, "%f ", h[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

int main() {
    initialize();

    double t_start = omp_get_wtime();
    compute();
    double t_end = omp_get_wtime();

    write_output();
    printf("Computation completed in %f seconds.\n", t_end - t_start);
    return 0;
}