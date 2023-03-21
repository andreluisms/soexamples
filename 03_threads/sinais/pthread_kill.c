/**
 * Um programa mostrando sinais e threads
 * Para compilar:
 * gcc pthread_kill.c -lpthread -o pthread_kill
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

//Funcao estatica que exibe uma mensagem estilo print_log 
static void print_log(const char *msg) {
  time_t t = time(NULL);
  printf("%s\t%s\n\n", ctime(&t), msg);
}

// Finaliza a thread
static void handler(int signum){
  pthread_exit(NULL);
}

void *thread(void *arg){
  //Estrutura de dados que representa sinal
  static sigset_t mask;  
  //inicializa o sinal para vazio
  sigemptyset(&mask);
  //Adiciona sinal SIGUSR1 para mask
  sigaddset(&mask, SIGUSR1);

  print_log("[thread] Bloqueia sinal SIGUSR1");
  if (pthread_sigmask(SIG_BLOCK, &mask, NULL) != 0) {
    perror("[thread] Nao foi possivel bloquear sinal");
    exit(1);
  }
  print_log("[thread] Faz algo...");

  sleep(10);

  print_log("[thread] Desbloqueia sinal SIGUSR1");
  if (pthread_sigmask(SIG_UNBLOCK, &mask, NULL) != 0) {
    perror("[thread] Nao foi possivel desbloquear sinal");
    exit(1);
  }
  print_log("[thread] Não chega aqui");
  return NULL;
}

int main(int argc, char *argv[])
{
  pthread_t tid;
  // Associa o método handler a SIGUSRS
  signal(SIGUSR1, handler);
  print_log("[main] Criando a thread...");
  if (pthread_create(&tid, NULL, thread, NULL) != 0) {
    perror("[main] Falha na criação da Thread");
    exit(1);
  }
  sleep(5);

  print_log("[main] Enviando sinal SIGUSR1 a thread...");

  pthread_kill(tid, SIGUSR1);
  pthread_join(tid, NULL);

  print_log("[main] Thread terminou.");
  return 0;
}
