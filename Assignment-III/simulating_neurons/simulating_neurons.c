#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define NEURONS 1000
#define STEPS 500
#define THRESHOLD 50.0

double potentials[NEURONS];
int firings[NEURONS];

void simulate() {
    int max_threads = omp_get_max_threads();
    FILE **files = malloc(max_threads * sizeof(FILE *));

    #pragma omp parallel shared(files)
    {
        int tid = omp_get_thread_num();

        char filename[64];
        snprintf(filename, sizeof(filename), "neuron_output_%d.txt", tid);
        files[tid] = fopen(filename, "w");

        #pragma omp barrier

        #pragma omp single
        {
            for (int i = 0; i < NEURONS; i++) {
                #pragma omp task firstprivate(i)
                {
                    int exec_tid = omp_get_thread_num();
                    FILE *f = files[exec_tid];
                    unsigned int seed = (unsigned int)time(NULL) ^ (unsigned int)(i * 2654435761u);

                    for (int step = 0; step < STEPS; step++) {
                        potentials[i] += rand_r(&seed) % 10;
                        if (potentials[i] > THRESHOLD) {
                            firings[i]++;
                            potentials[i] = 0;
                        }
                        fprintf(f, "%d %d %f\n", step, i, potentials[i]);
                    }
                }
            }

            #pragma omp taskwait
        }

        fclose(files[tid]);
    }

    free(files);
}

int main() {
    srand(time(NULL));
    for (int i = 0; i < NEURONS; i++) {
        potentials[i] = rand() % 20;
        firings[i] = 0;
    }
    simulate();

    FILE *fmerged = fopen("neuron_output.txt", "w");
    if (fmerged != NULL) {
        int max_threads = omp_get_max_threads();
        for (int t = 0; t < max_threads; t++) {
            char filename[64];
            snprintf(filename, sizeof(filename), "neuron_output_%d.txt", t);

            FILE *fin = fopen(filename, "r");
            if (fin != NULL) {
                printf("Merging %s\n", filename);
                char line[256];
                while (fgets(line, sizeof(line), fin) != NULL) {
                    fputs(line, fmerged);
                }
                fclose(fin);
                remove(filename);
            } else {
                fprintf(stderr, "Could not open %s for merging\n", filename);
            }
        }
        fclose(fmerged);
    }
    
    FILE *fsummary = fopen("neuron_summary.txt", "w");
    for (int i = 0; i < NEURONS; i++) {
        fprintf(fsummary, "Neuron %d fired %d times\n", i, firings[i]);
    }
    fclose(fsummary);
    
    return 0;
}