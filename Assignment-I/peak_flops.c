#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


/* Number of independent FMA accumulators.
 * Must be >= CPU FMA pipeline depth (typically 4-10 for modern CPUs)
 * so the out-of-order engine can overlap them. 8 is safe for most arches. */
#define N_ACC     8

/* Inner loop unroll factor (must match N_ACC). */
#define UNROLL    8

/* Number of outer iterations — increase if runtime is too short. */
#define OUTER     200000000L   /* 2 × 10^8  */

/* ------------------------------------------------------------------ */

/* Returns wall-clock time in seconds using CLOCK_MONOTONIC. */
static double now(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

/* ------------------------------------------------------------------ */
/* Core FMA kernel                                                      */
/* ------------------------------------------------------------------ */
static double run_fma_kernel(long iterations)
{
    /* Initialise accumulators to different non-zero values */
    double a0 = 1.1, a1 = 1.2, a2 = 1.3, a3 = 1.4;
    double a4 = 1.5, a5 = 1.6, a6 = 1.7, a7 = 1.8;

    const double mul = 1.0000001;
    const double add = 0.0000001;

    double t_start = now();

    for (long i = 0; i < iterations; i++) {
        a0 = a0 * mul + add;
        a1 = a1 * mul + add;
        a2 = a2 * mul + add;
        a3 = a3 * mul + add;
        a4 = a4 * mul + add;
        a5 = a5 * mul + add;
        a6 = a6 * mul + add;
        a7 = a7 * mul + add;
    }

    double elapsed = now() - t_start;

    double sink = a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7;
    if (sink == 0.0) printf("WARNNING: sink zero!!\n");

    return elapsed;
}

/* ------------------------------------------------------------------ */

int main(void)
{
    printf("===========================================\n");
    printf("  Peak FLOP/s benchmark (FMA chain)\n");
    printf("===========================================\n");
    printf("  Accumulators : %d\n", N_ACC);
    printf("  Iterations   : %ld\n", OUTER);

    /* --- Single-core measurement ----------------------------------- */
    printf("\n[Single core]\n");

    /* Warm-up pass (fills caches, stabilises frequency / boost). */
    run_fma_kernel(OUTER / 10);

    /* Timed pass. */
    double elapsed = run_fma_kernel(OUTER);

    /* Each iteration performs N_ACC FMA ops = N_ACC * 2 FLOP. */
    double total_flop = (double)OUTER * N_ACC * 2.0;
    double gflops     = total_flop / elapsed * 1e-9;

    printf("  Elapsed      : %.4f s\n",   elapsed);
    printf("  Total FLOP   : %.3e\n",     total_flop);
    printf("  Throughput   : %.2f GFLOP/s (scalar / auto-vec)\n", gflops);

    /* --- OpenMP multi-core (only compiled when -fopenmp is set) ---- */
#ifdef _OPENMP
    #include <omp.h>
    int n_threads = omp_get_max_threads();
    printf("\n[Multi-core — %d OpenMP threads]\n", n_threads);

    double t0 = now();

    #pragma omp parallel
    {
        run_fma_kernel(OUTER);
    }

    double elapsed_omp = now() - t0;
    double total_flop_omp =  (double)OUTER * N_ACC * 2.0 * n_threads;
    double gflops_omp     = total_flop_omp / elapsed_omp * 1e-9;

    printf("  Elapsed      : %.4f s\n",   elapsed_omp);
    printf("  Throughput   : %.2f GFLOP/s (%d threads)\n",
           gflops_omp, n_threads);
    printf("  Per thread   : %.2f GFLOP/s\n", gflops_omp / n_threads);
#endif

    return 0;
}
