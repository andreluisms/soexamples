/**
 * Autor: Andre Luis Meneses Silva 
 * Programa mostrando o método clone
 * Para compilar:
 *     gcc -o clone clone.c 
 * Para executar
 * ./clone 1 2 3 4
 * Onde os valores representam os ids de cada thread
 */

#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
const int STACK_SIZE=65536; // Tamanho da Stack (65536 bytes ou 64 KiB). 


// Codigo da Thread
int thread_code(void *arg){
   int i = 0;
   int n = atoi(arg);
   printf("Executando na tarefa filha %d \n", n);
   for ( i = 1 ; i <= 10 ; i++ )
      printf("\t thread(%d) = %d * %d = %d\n", n, n, i, (n*i));
   printf("\n");
   return 0;
}
//argc = Quantidade de Threads
//argv = 
void main(int argc, char *argv[]){

   // Ponteiro para a base e topo da Stack
   void* stack_base[argc-1]; 
   void* stack_top[argc-1];
   // ID de cada thread
   int  pid[argc-1];

   for (int j = 1; j < argc; j++){
     // Alocacao das Stacks de cada thread -> malloc aloca e devolve a posicao inicial
   	 stack_base[j-1] = malloc(STACK_SIZE);

     if(stack_base[j-1]==NULL) {
        perror("malloc");
        exit(1);
     }  
     // Topo da stack = base + tamanho da stack
     stack_top[j-1] = stack_base[j-1] + STACK_SIZE;
   }

   printf ("Foi alocado espaco para (%d) threads\n", argc-1);
   for (int j = 1; j < argc; j++){
        // Clone = Cria um processo filho
        // CLONE_VM  = mesmo espaco de memória
        // CLONE_FS =  mesma informação do sistema de arquivos  
        // CLONE_FILES = mesma tabela de acesso a arquivos 
        // CLONE_SIGHAND = mesma tabela de sinais
        pid[j-1] = clone(thread_code, stack_top[j-1], CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND, argv[j]);
        if (pid[j-1] < 0) { 
            printf("Erro: Nao foi possivel criar a thread.\n");
            exit(EXIT_FAILURE);
        }
   }

   // Aguarda pelo término das threads
   for (int j = 1; j < argc; j ++)
      wait(&pid[j-1]);

   // Desaloca a stack de cada thread
   for (int j = 1; j < argc; j++){
     free(stack_base[j-1]);
   }
   printf("Processos filho finalizado.\n");
}
