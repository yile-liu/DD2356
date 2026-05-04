#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#ifndef N
#define N 500       // Grid size
#endif

#ifndef ITER
#define ITER 1000  // Number of iterations
#endif

#define DT 0.01  // Time step
#define DX 1.0   // Grid spacing

#ifndef SCHED
#define SCHED runtime
#endif

#ifndef INIT
#define INIT flat   // Default initial condition
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define _STR(...) #__VA_ARGS__
#define STR(...) _STR(__VA_ARGS__)
#define OMP_FOR _Pragma(STR(omp parallel for collapse(2) schedule(SCHED)))

#define _CONCAT(a,b) a##b
#define CONCAT(a,b) _CONCAT(a,b)
#define INIT_FUNC CONCAT(init_, INIT)

double h[N][N], u[N][N], v[N][N];
double h_new[N][N], u_new[N][N], v_new[N][N];
double G = 9.8;

/* ---------- Classical initial conditions ---------- */

// 1. Flat / quiescent surface (no dynamics, control case)
void init_flat() {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            h[i][j] = 1.0;
            u[i][j] = 0.0;
            v[i][j] = 0.0;
        }
}

// 2. Centered Gaussian bump on a flat background
void init_gaussian() {
    const double cx = N / 2.0, cy = N / 2.0;
    const double sigma = N / 16.0;
    const double A = 0.5;
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            double dx = i - cx, dy = j - cy;
            h[i][j] = 1.0 + A * exp(-(dx*dx + dy*dy) / (2.0 * sigma * sigma));
            u[i][j] = 0.0;
            v[i][j] = 0.0;
        }
}

// 3. Dam-break: step discontinuity (classic Riemann problem)
void init_dam_break() {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            h[i][j] = (j < N / 2) ? 2.0 : 1.0;
            u[i][j] = 0.0;
            v[i][j] = 0.0;
        }
}

// 4. Droplet: narrow & tall Gaussian (raindrop impact)
void init_droplet() {
    const double cx = N / 2.0, cy = N / 2.0;
    const double sigma = N / 64.0;
    const double A = 1.0;
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            double dx = i - cx, dy = j - cy;
            h[i][j] = 1.0 + A * exp(-(dx*dx + dy*dy) / (2.0 * sigma * sigma));
            u[i][j] = 0.0;
            v[i][j] = 0.0;
        }
}

// 5. Two Gaussians (wave interference)
void init_double_gaussian() {
    const double cx1 = N / 3.0,     cy1 = N / 3.0;
    const double cx2 = 2.0 * N / 3.0, cy2 = 2.0 * N / 3.0;
    const double sigma = N / 16.0;
    const double A = 0.5;
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            double dx1 = i - cx1, dy1 = j - cy1;
            double dx2 = i - cx2, dy2 = j - cy2;
            double s2 = 2.0 * sigma * sigma;
            h[i][j] = 1.0
                    + A * exp(-(dx1*dx1 + dy1*dy1) / s2)
                    + A * exp(-(dx2*dx2 + dy2*dy2) / s2);
            u[i][j] = 0.0;
            v[i][j] = 0.0;
        }
}

// 6. Cosine bell: smooth compactly supported bump (Williamson test-case style)
void init_cosine_bell() {
    const double cx = N / 2.0, cy = N / 2.0;
    const double R = N / 8.0;
    const double A = 0.5;
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            double dx = i - cx, dy = j - cy;
            double r = sqrt(dx*dx + dy*dy);
            h[i][j] = (r < R) ? 1.0 + A * 0.5 * (1.0 + cos(M_PI * r / R))
                              : 1.0;
            u[i][j] = 0.0;
            v[i][j] = 0.0;
        }
}

// 7. Sinusoidal standing-wave initial condition
void init_sinusoidal() {
    const double A = 0.1;
    const double k = 2.0 * M_PI / N;
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            h[i][j] = 1.0 + A * sin(k * i) * sin(k * j);
            u[i][j] = 0.0;
            v[i][j] = 0.0;
        }
}

void initialize() {
    INIT_FUNC();
}

void compute() {
    for (int iter = 0; iter < ITER; iter++) {
        OMP_FOR
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

        OMP_FOR
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
    char fname[256];
    snprintf(fname, sizeof(fname), "output_%s.txt", STR(INIT));
    FILE *f = fopen(fname, "w");
    if (!f) {
        fprintf(stderr, "Cannot open %s\n", fname);
        return;
    }
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
    printf("[init=%s schedule=%s threads=%d] Computation completed in %f seconds.\n",
           STR(INIT), STR(SCHED), omp_get_max_threads(), t_end - t_start);
    return 0;
}
