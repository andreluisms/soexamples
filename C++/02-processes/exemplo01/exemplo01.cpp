/*
 * Exemplo01 - Exibe o comportamento do novo processo,
 * criado pelo fork() 
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int valor = 5;

int main()
{
	pid_t pid;

	pid = fork(); //Filho e pai continuam desse trecho
	
	if (pid == 0) { /* processo filho */
		valor += 15;
		return 0;
	}
	else if (pid > 0) { /* processo pai */
		wait(NULL);
		printf ("Processo pai: valor = %d\n",valor); /* LINE A */
		return 0;
	}
}
