#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>

#define SIZE 512

static char fichero[]="texto.txt";
void* leer_fnc();
void* escribir_fnc();
void* leer_fichero_fnc();
int descriptor;
char buffer[SIZE];
int flag=0;//0 leer de teclado, 1 escribir al fichero, 2 leer del fichero

pthread_t leer, escribir, leer_fichero;

int main(void)
{
	pthread_create(&leer, NULL, &leer_fnc, NULL);
	pthread_create(&escribir, NULL, &escribir_fnc, NULL);
	pthread_create(&leer_fichero, NULL, &leer_fichero_fnc, NULL);
	pthread_join(leer, NULL);
	pthread_join(escribir, NULL);
	pthread_join(leer_fichero, NULL);
	
	
	return 0;
}
void* leer_fnc()
{
	printf("Introduce el texto que quieres escribir: ");
	fgets(buffer, SIZE, stdin);
	flag=1;
	return 0;
}
void* escribir_fnc()
{
	while (flag!=1);
	if ((descriptor=open(fichero, O_RDWR))==-1)
	{
		perror("error abriendo el puto fichero\n");
		exit(-1);
	}
	write(descriptor, buffer, strlen(buffer));
	//close (descriptor);
	flag=2;
	return 0;
}
void* leer_fichero_fnc()
{
	int bytes_leidos;
	while(flag!=2);
	lseek(descriptor, 0, SEEK_SET);
	while((bytes_leidos=read(descriptor, buffer, SIZE))>0)
	{
		printf("%s", buffer);
	}
	close (descriptor);
	return 0;
}

