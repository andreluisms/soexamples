/**
 * Um programa simples, mostrando como criar threads em C.
 * Para compilar:
 * gcc -pthread criandothreads.c -o criandothreads
 *  
 * Adaptado de
 * Operating System Concepts  - Ninth Edition
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int soma; // Dado compartilhado entre as threads

void *somador(void *param); //Método executado pela thread

int main(int argc, char *argv[])
{
    if (argc != 2) {
	    fprintf(stderr,"sintaxe: ./criandothreads <valor inteiro maior que 0>\n");
	    return -1;
    }

    if (atoi(argv[1]) < 0) {
	    fprintf(stderr,"Argumento %d nao deve ser negativo\n",atoi(argv[1]));
	    return -1;
    }


    pthread_t thread; //cria variável do tipo thread
    pthread_attr_t attr; // cria variável do tipo atributo de thread

    pthread_attr_init(&attr); // attr com valores padroes
    pthread_create(&thread,&attr,somador,argv[1]); // cria a thread (thread, atributo, funcao, args)

    pthread_join(thread,NULL);     // Nesse ponto, main aguarda por thread
    printf("soma = %d\n",soma);
}

/**
 * Soma a sequencia de 1 ate somador
 */
void *somador(void *param) 
{
    int i, ultimo = atoi(param);
    soma = 0;

	if (ultimo > 0) {
		for (i = 1; i <= ultimo; i++)
			soma += i;
	}
	pthread_exit(0);
}
