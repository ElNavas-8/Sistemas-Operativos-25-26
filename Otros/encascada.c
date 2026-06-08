#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#define LIMITE 10

pthread_t array[LIMITE];
int n=0;

void *creaThread();
void calcula();

int main (void)
{
	pthread_create(&array[n], NULL, &creaThread, NULL);
	pthread_join(array[n], NULL);
	return 0;
}

void *creaThread()
{
		printf("He nacido. Soy el hilo con ID %lu\n", pthread_self());
		
		n++;
		calcula();
		if (n<LIMITE)
		{
			pthread_create(&array[n], NULL, &creaThread, NULL);
			pthread_join(array[n], NULL);
		}
		else
		{
			char g[10];
			fgets(g, sizeof(g), stdin);
		}
		printf("El hilo con ID %lu acaba su ejecución\n", pthread_self());
		return 0;
}
void calcula()
{
	long long unsigned t;
	for (t=0;t<(0xFFFFFFF);t++);
}






















