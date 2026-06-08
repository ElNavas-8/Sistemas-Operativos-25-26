//Versión de leer por teclado, escribir a disco, leer de disco
//con Mutex como sincronización

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>

#define SIZE 512
pthread_mutex_t lock_escribe, lock_leefichero;

static char fichero[]="texto.txt";
void* leer_fnc();
void* escribir_fnc();
void* leer_fichero_fnc();
int descriptor;
char buffer[SIZE];


pthread_t leer, escribir, leer_fichero;

int main(void)
{
	pthread_create(&leer, NULL, &leer_fnc, NULL);
	usleep(20);
	pthread_create(&escribir, NULL, &escribir_fnc, NULL);
	usleep(20);
	pthread_create(&leer_fichero, NULL, &leer_fichero_fnc, NULL);
	pthread_join(leer, NULL);
	pthread_join(escribir, NULL);
	pthread_join(leer_fichero, NULL);
	pthread_mutex_destroy(&lock_escribe);
	pthread_mutex_destroy(&lock_leefichero);
	
	return 0;
}
void* leer_fnc()
{
	pthread_mutex_lock(&lock_escribe);
	printf("Introduce el texto que quieres escribir: ");
	fgets(buffer, SIZE, stdin);
	pthread_mutex_unlock(&lock_escribe);
	return 0;
}
void* escribir_fnc()
{
	pthread_mutex_lock(&lock_leefichero);
	pthread_mutex_lock(&lock_escribe);
	if ((descriptor=open(fichero, O_RDWR))==-1)
	{
		perror("error abriendo el puto fichero\n");
		exit(-1);
	}
	write(descriptor, buffer, strlen(buffer));
	pthread_mutex_unlock(&lock_leefichero);
	pthread_mutex_unlock(&lock_escribe);
	return 0;
}
void* leer_fichero_fnc()
{
	pthread_mutex_lock(&lock_leefichero);
	int bytes_leidos;
	lseek(descriptor, 0, SEEK_SET);
	while((bytes_leidos=read(descriptor, buffer, SIZE))>0)
	{
		buffer[SIZE]='\0';
		printf("%s", buffer);
	}
	close (descriptor);
	pthread_mutex_unlock(&lock_leefichero);
	return 0;
}

