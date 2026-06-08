#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h> 


void sigfpe_handler(int num);
void divide();
int espera();

pid_t division;
static int *resetea, *esperame;

int main (void)
{
	
	signal(SIGFPE, sigfpe_handler);
	resetea=mmap(NULL, sizeof (*resetea), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	esperame=mmap(NULL, sizeof (*esperame), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*resetea=1;
	*esperame=0;
	division=fork();
	if (division==0)
	{
		divide();
	}
	else if (division>0)
	{
		espera();
	}
	return 0;
	
}
void divide()
{
	while (1)
	{
		while(*esperame==1);
		int n1, n2;
		printf("primer número: ");
		scanf("%d", &n1);
		printf("segundo número: ");
		scanf("%d", &n2);
		int resultado=n1/n2;
		printf("El resultado es %d\n", resultado);
	}
	
}

void sigfpe_handler(int num)
{
	if (division==0)
	{
		puts("mira que eres pinche güey...\n");
		*resetea=1;
		exit(0);
	}
	if (division>0)
	{
		//NO HAGO NADA 
	}
}
int espera()
{
	while(1)
		{
			wait(NULL);
			if (*resetea==1)
			{
				*resetea=0;
				division=fork();
				if (division==0)
				{
					divide();
				}
				else//padre
				{
					espera();//llamada recursiva
				}
			}
		}
}
