#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/types.h>
#define SIZE 4096

int main (void)
{
	pid_t hijo;
	int tuberia[2];
	char buffer[SIZE];
	pipe (tuberia);
	
	if ((hijo=fork())<0)
	{
		perror("error al crear el hijo\n");
		exit(-1);
	}
	else if (hijo>0)//Padre
	{
		close(tuberia[1]);
		read (tuberia[0], buffer, SIZE);
		printf("El hijo me acaba de enviar: \n%s\n", buffer);
		wait(NULL);
		close(tuberia[0]);
	}
	else 
	{
		close(tuberia[0]);
		dup2 (tuberia[1], STDOUT_FILENO);
		puts("Holaaaaaaaaaaaaa");
		execl("./032_esclavo", "032_esclavo", NULL);
		puts ("Idiota el que lea esta línea");
	}
	puts("Soy el padre y el programa finaliza");
	return 0;
}
