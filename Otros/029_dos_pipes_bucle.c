//Programa que usa dos pipes. El padre lee dos numeros, los manda al
//hijo y este le devuelve la suma

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (void)
{
	int tuberia_hijo[2], tuberia_padre[2], num1, num2, suma;
	pid_t hijo;
	
	if (pipe(tuberia_hijo)<0 || pipe(tuberia_padre)<0)
	{
		perror("Se ha producido un error al crear el pipe\n");
		return -1;
	}
	hijo=fork();
	if (hijo>0)
	{
		close (tuberia_padre[0]);
		close (tuberia_hijo[1]);
		printf("escribe el primer número: ");
		scanf("%d", &num1);
		while (num1!= -1)
		{
			printf("\nEscribe el segundo número: ");
			scanf("%d", &num2);
			write(tuberia_padre[1], &num1, sizeof(num1));
			write(tuberia_padre[1], &num2, sizeof(num2));
			read (tuberia_hijo[0], &suma, sizeof(suma));
			printf("La suma es %d\n", suma);
			printf("Escribe el primer número: ");
			scanf("%d", &num1);
		}
		puts("Voy a morir, me cargo al chaval");
		kill(hijo, SIGKILL);
	}
	if (hijo==0)
	{
		close (tuberia_padre[1]);
		close (tuberia_hijo[0]);
		while(1)
		{
			read(tuberia_padre[0], &num1, sizeof(num1));
			read(tuberia_padre[0], &num2, sizeof(num2));
			suma=num1+num2;
			write(tuberia_hijo[1], &suma, sizeof(suma));
		}
	}
	puts("Esta línea solo debe sacarla el papi");
}
