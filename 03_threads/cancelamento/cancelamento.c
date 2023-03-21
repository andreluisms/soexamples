//gcc cancelamento.c -lpthread -o cancelamento

#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

void tratador_erro(int en, char* msg){
  errno = en;
  printf("%s", msg); 
  exit(EXIT_FAILURE);
}

static void * thread_func(void *ignored_argument){
  printf("Thread comeca execucao\n");
  sleep(3);
  printf("Thread nao cancelada\n");
  return NULL;
}

int
main(void)
{
 pthread_t thr;
 void *res;
 int s;

 s = pthread_create(&thr, NULL, &thread_func, NULL);
 if (s != 0)
   tratador_erro(s, "pthread_create");
 sleep(2);  

 printf("main(): Enviando requisicao de cancelamento\n");
 s = pthread_cancel(thr);
 if (s != 0)
   tratador_erro(s, "pthread_cancel");
 s = pthread_join(thr, &res);
 if (s != 0)
   tratador_erro(s, "pthread_join");

 if (res == PTHREAD_CANCELED)
   printf("main(): thread foi cancelada\n");
 else
   printf("main(): thread nao foi cancelada\n");

 exit(EXIT_SUCCESS);
}