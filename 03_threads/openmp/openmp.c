/**
 * Programa mostrando OpenMP
 * Para compilar:
 *  gcc openmp.c -lgomp -o openmp
 *  
 */
#include <omp.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    // codigo sequencial

    #pragma omp parallel
    {
        // Codigo paralelo
        // Cria x threads de acordo com a quantidade de cores presentes em sua CPU.
        printf("Thread id: %d\n", omp_get_thread_num());
    }
        // codigo sequencial
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int b[] = {9, 10, 11, 12, 13, 14, 15, 16};
    int c[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int i = 0;
    #pragma omp parallel for
        for (int i = 0; i < 8; i++) {
            c[i] = a[i] + b[i];
            printf("Thread id: %d e c[%d] possui valor: %d\n", omp_get_thread_num(), i, c[i]);
        }

    return 0;
}
