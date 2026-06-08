#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

void* es_primo ();
void* fibonacci ();
pthread_t hilo_fibonacci, hilo_primo;

int main(void)
{
	//unsigned int n1=10000,n2=234235235;
	//fibonacci(n1);
	//es_primo(n2);
	pthread_create(&hilo_fibonacci, NULL, fibonacci, NULL);
	pthread_create(&hilo_primo, NULL, es_primo, NULL);
	pthread_join(hilo_fibonacci, NULL);
	pthread_join(hilo_primo, NULL);
	
	return 0;
	
}
void *fibonacci()
{
	unsigned long int i, n=10000, t1 = 0, t2 = 1, siguiente;
    for (i = 1; i <= n; ++i) {
        printf("%lu, ", t1);
        siguiente = t1 + t2;
        t1 = t2;
        t2 = siguiente;
    }
    return NULL;
}	
void* es_primo ()
{
	int num=234235235;
	int flag=1;// 1 si es primo, 0 si no lo es
	for (int i=2; i<num; i++)
	{
		if (num%i == 0)
		{
			flag=0;
			//break;
		}
	}
	if (flag==1)
		printf("\nEl numero %d es primo\n", num);
	else 
		printf("\nEl numero %d no es primo\n", num);
		
	return NULL;
}


