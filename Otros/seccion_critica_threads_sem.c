#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

#define LIMITE 1000000

void *incrementa();
void *decrementa();

static int global_var=0;
sem_t *mutex;

int main()
{
	pthread_t suma, resta;
	mutex=sem_open("/semaforo", O_CREAT, S_IRUSR | S_IWUSR, 1);
	pthread_create(&suma, NULL, &incrementa, NULL);
	pthread_create(&resta, NULL, &decrementa, NULL);
	pthread_join(resta, NULL);
	pthread_join(suma, NULL);
	printf("El valor final de la variable es %d\n", global_var);
	sem_close(mutex);
	sem_unlink("/semaforo");
	return 0;
}
void *incrementa()
{
	int i;
	puts("Comienza hilo suma\n");
	for (i=0;i<LIMITE;i++)
	{
		sem_wait(mutex);
		global_var=global_var+1;
		sem_post(mutex);
	}
	printf("Suma: el valor final de la variable es %d\n", global_var);
	return 0;
}
void *decrementa()
{
	int i;
	puts("Comienza hilo resta\n");
	for (i=0;i<LIMITE;i++)
	{
		sem_wait(mutex);
		global_var=global_var-1;
		sem_post(mutex);
	}
	printf("resta:valor final de la variable es %d\n", global_var);
	return 0;
}

