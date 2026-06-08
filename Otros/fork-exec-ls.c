/* Este programa crea un proceso a través de fork. El hijo pregunta si 
 * se quieres lanzar el comando 'ls' y y lo ejecuta mediante una 
 * instrucción 'exec'. El padre espera pacientemente a que el hijo acabe
 * mediante la instrucción 'wait' y finaliza su ejecución*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>

int main (void)
{
	pid_t proceso; // Creamos un variable para almacenar el proceso hijo
	char respuesta; // Variable tipo caracter para almacenar la respuesta
	proceso=fork(); // creamos el proceso hijo
	
	if (proceso==0) //Si proceso vale 0, se trata del proceso hijo.
	{
		printf("Soy el hijo. Quieres lanzar el comando ls? (y|n): ");
		//Utilizamos %c como especificador de formato para el char
		scanf ("%c", &respuesta);
		//Para comparar un caracter utilizamos comillas simples
		if (respuesta=='y')
		{
			printf ("Soy un hijo suicida...ahí voy...!!\n");
			//Ejecutamos la instrucción ls. El proceso hijo se destruye
			execl("/bin/ls", "ls", NULL);
			//Esta línea nunca debiera ejecutarse ya que el proceso hijo debiera haber muerto
			printf("Puuuuuta vida...!!");
		}
		else
		{
			//Función que imprime por pantalla una cadena de texto
			puts("Pues nada, tu te lo pierdes\n");
			exit(0);
		}
	}
	else if (proceso>0)//Este es el proceso padre
	{
		//Esperamos a que el hijo acabe
		wait (NULL);
		printf("Mi hijo murió...larga vida a mi hijo...!\n");
	}
	return 0;
}
