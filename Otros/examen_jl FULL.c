#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <math.h>

void *master_f();
void *escribir_por_pantalla();
void *calcula_primo();
void *es_fibonnaci();

unsigned long long factorial (int);
int es_primo (unsigned long long int);

int lanzar_fibonacci=0, lanzar_primo=0;
int seguir_leyendo=1;//1 seguimos leyendo números, 0 acabamos
static int hayDato=0;
int dato;
unsigned long long fact;


int main ()
{
	system("clear");
	pthread_t master, escribe, primo, fibonacci;
	pthread_create(&master, NULL, &master_f, NULL);
	pthread_create(&escribe, NULL, &escribir_por_pantalla, NULL);
	pthread_create(&primo, NULL, &calcula_primo, NULL);
	pthread_create(&fibonacci, NULL, &es_fibonnaci, NULL);
	pthread_join(master, NULL);
	pthread_join(escribe, NULL);
	

	return 0;
}

void *master_f()
{
	while (seguir_leyendo==1)
	{
		while(hayDato==1) usleep(10);
		printf("Soy el hilo %u. Introduce un número:", (unsigned int)pthread_self());
		scanf("%d", &dato);
		if (dato==-1)
		{
			seguir_leyendo=0;
			hayDato=1;
			break;
		}
		hayDato=1;	
	}
	return 0;
}
void *escribir_por_pantalla()
{
	while (seguir_leyendo==1)
	{
		while(hayDato==0);
		if (seguir_leyendo==0)break;
		printf("\nSoy el hilo %u y el factorial de %d es %llu\nVoy a realizar los otros calculos", (unsigned int)pthread_self(), dato, factorial(dato));
		fact=fact-1;
		printf(" para %llu\n", fact);
		lanzar_fibonacci=1;
		lanzar_primo=1;
		while(lanzar_fibonacci!=0 || lanzar_primo!=0);
		hayDato=0;	
	}
	return 0;
}
unsigned long long factorial(int num)
{
	int i; 
	for (i=1, fact=1;i<=num;i++)
	{
		fact=fact*i;
	}
	printf("%llu\n", fact);
	return fact;
}
int es_primo (unsigned long long num)
{
	int flag=1;// 1 si es primo, 0 si no lo es
	for (unsigned long long int i=2; i<num; i++)
	{
		if (num%i == 0)
		{
			flag=0;
			break;
		}
	}
	if (flag==1)
		return 1;
	else 
		return 0;
}
void *calcula_primo()
{
	while (1)
	{
		while(lanzar_primo==0)usleep(10);
		if (es_primo(fact))
		{
			printf("Soy el hilo %u y El numero %llu es primo\n", (unsigned int)pthread_self(), fact);
		}
		else
		{
			printf("Soy el hilo %u y El numero %.llu no es primo\n", (unsigned int)pthread_self(), fact);
		}
		lanzar_primo=0;
	}	
	return NULL;
}
void *es_fibonnaci()
{
	while (1)
	{
		while(lanzar_fibonacci==0)usleep(10);
		long double i, t1, t2, siguiente;
		for (t1 = 0, t2= 1; t2 <= fact; ++i) {
			siguiente = t1 + t2;
			t1 = t2;
			t2 = siguiente;
		}
		if (t1==fact)
		{
			printf("Soy el hilo %u y El numero %.llu pertenece a la serie Fibonacci\n",(unsigned int)pthread_self(), fact);
		}
		else
		{
			printf("Soy el hilo %u y El numero %.llu no pertenece a la serie Fibonacci\n", (unsigned int)pthread_self(), fact);
		}
		lanzar_fibonacci=0;
	}
	
	return NULL;
}
