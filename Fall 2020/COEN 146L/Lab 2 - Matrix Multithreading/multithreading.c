/*
Name: Ruchir Mehta
Date: October 1st, 2020
Title: Lab 2, Part 1: Multithreading in C
Description: Use parallelism for large scale multi-D matrix multiplication
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define N 1024
#define M 1024
#define L 1024

// array of size 1024 
pthread_t tids[N];  // thread id

// instantiate matrices
double matrixA[N][M], matrixB[M][L], matrixC[N][L] = {0.0};

void printMa(int x, int y, double matrix[x][y])
{
    int i, j = 0;
    for (i = 0; i < x; i++)
    {
        for (j = 0; j < y; j++)
        {
            printf("%lf   ", matrix[i][j]);
        }
        printf("\n");
    }
}

void *start_routine(void *arg)
{
    int j, k = 0;
    int i = *(int *)arg;

    for (j = 0; j < L; j++)
    {
        for (k = 0; k < M; k++)
        {
            matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
        }
    }
    free(arg);
}

int main()
{
    srand(time(NULL));
    int i,j,k = 0;

    // matrix A creation
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            matrixA[i][j] = rand();
        }
    }

    // matrix B creation
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < L; j++)
        {
            matrixB[i][j] = rand();
        }
    }

    // matrix C = A * B
    for (i = 0; i < N; i++)
    {
        int *arg = malloc(sizeof(int));
        *arg = i;
        pthread_create(&tids[i], NULL, start_routine, arg);
    }

    // Necessary outputs
    printf("Matrix A:\n");
    printMa(N, M, matrixA);

    printf("\n\nMatrix B:\n");
    printMa(M, L, matrixB);

    printf("\n\nMatrix C:\n");
    printMa(N, L, matrixC);

  return 0;
}
