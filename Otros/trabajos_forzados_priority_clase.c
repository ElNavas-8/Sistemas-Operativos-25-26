#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *calcula();

int main(void)
{
	pthread_t hilo;

	pthread_create(&hilo,NULL,&calcula,NULL);
	pthread_join(hilo, NULL);
	return 0;
}
void *calcula()
{
	char g[10];
	for (int i=0;i<5;i++)
	{
		
		long long unsigned t;
		for (t=0;t<(0xFFFFFFFF);t++);
	}
	printf("Hemos acabado, comprueba datos\n");
	gets(g);
	pthread_exit(0);
}
