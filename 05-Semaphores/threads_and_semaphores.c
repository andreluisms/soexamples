// C program to demonstrate working of Semaphores
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
  
sem_t semaphore;
  
void* show(void* arg)
{
    char* name = (char*) arg;
    //wait
    sem_wait(&semaphore);
    for (int i =0; i<5; i++){
        printf("Hello %s\n", name);
        sleep(1);
    }
    sem_post(&semaphore);
}
  
  
int main()
{
    sem_init(&semaphore, 0, 2);
    pthread_t t1,t2,t3,t4,t5,t6;
    pthread_create(&t1,NULL,show,"Thread-1");
    pthread_create(&t2,NULL,show,"Thread-2");
    pthread_create(&t3,NULL,show,"Thread-3");
    pthread_create(&t4,NULL,show,"Thread-4");
    pthread_create(&t5,NULL,show,"Thread-5");
    pthread_create(&t6,NULL,show,"Thread-6");

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    pthread_join(t5,NULL);
    pthread_join(t6,NULL);
    sem_destroy(&semaphore);
    return 0;
}