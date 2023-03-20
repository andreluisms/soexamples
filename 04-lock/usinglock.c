#include <stdio.h>    // std::cout
#include <pthread.h>         // std::thread
#include <string.h>
#include <unistd.h>


pthread_mutex_t lock;
int n_threads =100;


void* jobs (void* arg) {
    pthread_mutex_lock(&lock);
    printf("lock acquire() ------>Thread-%ld\n",pthread_self());
    pthread_mutex_unlock(&lock);
}

int main ()
{
    pthread_t threads[n_threads]; 
    char name[n_threads][15];
    for (int i = 0; i < n_threads; i++ )
        pthread_create(&threads[i],NULL,jobs,NULL);
    for (int i =0; i < n_threads; i++)
        pthread_join(threads[i],NULL);
    pthread_mutex_destroy(&lock);
}