/**
 * Um programa simples, mostrando como criar threads em C.
 * Para compilar:
 * gcc forkthread.c -lpthread -o forkthread
 * ps -T -p <pid>
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

int global1 = 0;
/**
 * Soma a sequencia de 1 ate somador
 */
void* criadorDeProcesso(void *param) 
{
	pid_t pid;
	pid = fork(); //Filho e pai continuam desse trecho
	if (pid < 0) { /* se pid < 0, filho nao foi criado */
		fprintf(stderr, "Falha na criacao do filho\n");
	}
	else if (pid == 0) {
		printf("PID do processo filho da thread: %d\n",getpid());
        global1+=1;
		printf("global1 do filho: %d\n",global1);
        sleep(2);
	}
	else { 
		printf("Eu sou a Thread pai %d\n",getpid());
		wait(NULL); // pai aguarda ate o filho completar
		printf("Final do processo filho\n");
		printf("global1 do pai: %d\n",global1);
        sleep(3);
	}
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
    pthread_t tid; //identificador da thread 
    pthread_attr_t attr; // atributos da thread
    pthread_attr_init(&attr); // associa parâmetros default a attr
    pthread_create(&tid,&attr,criadorDeProcesso,argv[1]); // metodo para criação da thread
    pthread_join(tid,NULL);     // Nesse ponto, thread pai aguarda pela thread filha
    printf("Fim da execucao do processo pai (%d)\n", getpid());
}


