/**
 * Um programa mostrando como tratar sinal.
 * Para compilar:
 * gcc tratador_kill.c -o tratador_kill
 */

#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void signal_handler(int sinal){
	if (sinal == SIGINT)
		printf("[Processo %d]: recebeu sinal: SIGINT (ctrl+c)\n", getpid());
	else if (sinal == SIGTSTP){
		printf("[Processo %d]recebeu sinal: SIGTSTP (ctrl + z) \n", getpid());
	} 
}

int main(void){
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		printf("\nNao foi possivel usar o tratador para SIGINT\n");
	if (signal(SIGTSTP, signal_handler) == SIG_ERR)
		printf("\nNao foi possivel usar o tratador para SIGTSTP\n");

  // Laço infinito, para captura do sinal.
	printf("Pressione ctrl+z ou ctrl+c ou use kill -SINAL PID:\n");
	while(1){
		sleep(1);
	}
	return 0;
}
