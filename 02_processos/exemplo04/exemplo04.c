/**
 * Ilustra como fazer a comunicacao entre processos no linux
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1

int main(void)
{
	char write_msg[BUFFER_SIZE] = "Seja bem vindo";
	char read_msg[BUFFER_SIZE];
	pid_t pid;
	int first_pipe[2];
	int second_pipe[2];
	int i;

	if (pipe(first_pipe) == -1) { //Cria um pipe unidirecional para comunicao entre processos
		fprintf(stderr,"Falha do primeiro pipe");
		return 1;
	}
 	if (pipe(second_pipe) == -1) {
                fprintf(stderr,"Falha do segundo pipe");
                return 1;
        }

	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Falha na geracao do processo filho");
		return 1;
	}

	if (pid > 0) {  // Codigo do processo pai
		printf("Endereco do pipe pai: ");
                printf("%p", &pipe);
		printf("\n");
		close(first_pipe[READ_END]); // Fecha primeiro pipe para leitura
		close(second_pipe[WRITE_END]); // Fecha segundo pipe para escrita

		/* escreve para o primeiro pipe */
		write(first_pipe[WRITE_END], write_msg, strlen(write_msg)+1); 

		/* Fecha o primeiro pipe para escrita */
		close(first_pipe[WRITE_END]);

		/* Le o resultado do segundo pipe */
		read(second_pipe[READ_END], read_msg, BUFFER_SIZE);
		printf("Processo pai leu >%s<\n", read_msg);
                printf("Processo pai write_msg: %s \n", write_msg);
	        printf("%p",write_msg);
                printf(": write_msg\n");
                
                // Fecha o segundo pipe para leitura.
		close(second_pipe[READ_END]);
	}
	else { // codigo do processo filho
		
		printf("Endereco do pipe filho: ");
 		printf("%p", &pipe);
                printf("\n");
                printf("%p", &write_msg);
                printf("\n");
                
		close(first_pipe[WRITE_END]); 
		close(second_pipe[READ_END]);

		
		read(first_pipe[READ_END], read_msg, BUFFER_SIZE); //le do primeiro pipe
		printf("Processo filho leu >%s<\n",read_msg);

		/* Processo filho inverte caracteres e devolve a msg para o pai*/
		for (i = 0; i < strlen(read_msg); i++) {
			if (isupper(read_msg[i]))
				write_msg[i] = tolower(read_msg[i]);
			else if (islower(read_msg[i]))
				write_msg[i] = toupper(read_msg[i]);
			else
				write_msg[i] = read_msg[i];
		}
                printf("Processo filho write_msg: %s\n", write_msg);
		write(second_pipe[WRITE_END], write_msg, strlen(write_msg)+1);
		
		close(first_pipe[READ_END]);
		close(second_pipe[WRITE_END]);
	}

	return 0;
}
