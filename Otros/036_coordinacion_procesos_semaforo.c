//Coordinación procesos mediante semaforo
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h> 

static int *numero;

int main (void)
{
	sem_t *semaforo;
	pid_t lee, escribe;
	semaforo=sem_open("/misemaforo", O_CREAT, S_IRUSR | S_IWUSR, 1);
	numero=mmap(NULL, sizeof *numero, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	
	lee=fork();
	if (lee>0)
	{
		escribe=fork();
	}
	if (lee==0) // Proceso lee
	{
		sem_wait(semaforo);
		puts("Introduce un número:");
		scanf("%d", *&numero);
		sem_post(semaforo);
		exit(1);
	}
	if (escribe==0)
	{
		usleep(10);
		sem_wait(semaforo);
		printf("El número es: %d", *numero);
		sem_post(semaforo);
		exit(1);
		
	}
	while (wait(NULL)>0);
	sem_close(semaforo);
	sem_unlink("/misemaforo");
	
	return 0;
}
