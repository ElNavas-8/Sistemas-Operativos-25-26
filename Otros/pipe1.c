#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (void)
{
	pid_t proceso; 
	//Siempre declaramos un array de dos elementos de tipo int para crear una tubería
	int tuberia[2];
	//Pasamos el array a la función pipe, para ya transformalo en una tubería
	pipe (tuberia);
	
	proceso=fork();
	if (proceso==0)//proceso hijo y lector
	{
		//Creamos una variable FILE, que almacenará un flujo de datos. 
		//OJO!!: estas variables se abren siempre como punteros, es decir, hay que poner un '*'
		//delante de su nombre.
		FILE *datos;
		int num;
		//Como el hijo va a leer datos, es decir, va a usar tuberia[0], cerramos el lado 
		//que no va a usar, es decir, tuberia[1]
		close(tuberia[1]);
		
		//Abrimos el flujo de datos, pasando a la funcion fdopen el lado de la tuberia que
		//vamos a usar y el modo de apertura, en este caso lectura ('r')
		datos=fdopen(tuberia[0], "r");
		
		//Leemos los datos que el padre pasa por la tuberia, utilizando la función
		//fscanf. Funciona igual que scanf pero indicando en un primer parametro de 
		//dónde queremos leer los datos. En este caso, del flujo de datos que acabamos 
		//de crear (datos), que está creado en base a tuberia[0]
		fscanf(datos, "%d", &num);
		printf("Hola soy el hijo y papa me ha pasado un %d\n", num);
		//Cuando acabemos de usar la tuberia, procedemos a cerrarla con fclose
		fclose(datos);
	}
	else if (proceso>0)//proceso padre y escritor
	{
		//El código del lado escritor es análogo al del lado lector, pero en este caso
		//utilizaremos el lado escritor de la tuberia, que siempre es el elemento 1
		//del array (en nuestro caso concreto, tuberia[1]
		FILE *datos;
		int num=5;
		close (tuberia[0]);
		//Al abrir el flujo de datos especificamos que este caso queremos escribir
		//en él, de modo que lo abrimos en modo escritura ('w')
		datos = fdopen(tuberia[1], "w");
		fprintf(datos, "%d", num);
		fclose(datos);
		wait(NULL);
		printf("Buen hijo, siempre coge lo que le mando...adios!\n");
	}
	return 0;
}
