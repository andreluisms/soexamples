/**
 * Exibe o pid dos processos pai e filho. 
 */

#include <stdio.h>

int main()
{
	printf("%d\n",getpid());
	fork();
	printf("%d\n",getpid());
	

	fork();
	printf("%d\n",getpid());

	fork();
	printf("%d\n",getpid());

	return 0;
}
