#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int data[1048576];
    double start, end;
    int count = 2000;
    for (int size = 1; size <= 1048576; size *= 2)
    {
        if (rank == 0)
        {
            double total_time = 0;
            for (size_t r = 0; r < count; r++)
            {
                start = MPI_Wtime();
                MPI_Send(&data, size, MPI_INT, 1, 0, MPI_COMM_WORLD);
                MPI_Recv(&data, size, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                end = MPI_Wtime();
                total_time += (end - start);
            }

            printf("Size: %d Bytes, RTT: %f microseconds\n", size * sizeof(int), total_time / count * 1e6);
        }
        else
        {
            for (size_t r = 0; r < count; r++)
            {
                MPI_Recv(&data, size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(&data, size, MPI_INT, 0, 0, MPI_COMM_WORLD);
            }
        }
    }
    MPI_Finalize();
    return 0;
}
