/**
 * Exemplo de criacao de processo filho usando fork e exec
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t pid;
	/* cria processo filho */
	pid = fork();

	if (pid < 0) { /* se pid < 0, filho nao foi criado */
		fprintf(stderr, "Falha na criacao do filho\n");
		return 1;
	}
	else if (pid == 0) { /* Processo filho */
		printf("PID do processo filho: %d\n",pid);
		execlp("/bin/ls","ls", NULL); //Nesse ponto, filho encapsula o programa ls
	}
	else { /* Processo pai */
		printf("Eu sou o pai %d\n",pid);
		wait(NULL); // pai aguarda ate o filho completar
		printf("Final do processo filho\n");
	}
    return 0;
}
