/* Versión modificada de comunicación mediante tuberías. 
 * En este caso el proceso hijo es el escritor, y pide números 
 * al usuario que va enviado al proceso lector (el padre) hasta
 * que el usuario introduce el valor -1, que será cuando el programa
 * finalice su ejecución*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main (void)
{
	pid_t hijo;
	int mi_tuberia[2], num;
	pipe(mi_tuberia);
	hijo=fork();
	if (hijo==0)
	{
		close (mi_tuberia[0]);
		FILE *stream;
		stream = fdopen (mi_tuberia[1], "w");
		do
		{
			printf("Soy el proceso hijo, introduce un número: ");
			scanf("%d", &num);
			fprintf(stream, "%d\n", num);
		}
		while (num!=-1);
		fclose(stream);
	}
	if (hijo>0)
	{
		FILE *stream;
		int c;
		close (mi_tuberia[1]);
		stream=fdopen(mi_tuberia[0], "r");
		do
		{
			fscanf(stream, "%d", &c);
			printf("El numero es %d\n", c);
		}
		while(c!=-1);
		fclose(stream);	
	
	}
}
