#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>//Para usar la función wait()


int main (void)
{
	pid_t proc; //declaramos una variable de tipo pid_t, que permite almacenar IDs de proceso
	proc=fork();//creamos el proceso hijo. A partir de esta linea 2 procesos se ejecutarán
	if (proc==0)//Si la variable proc es igual 0, sabemos que este es el proceso hijo
	{
		puts(" soy el hijo y me despido, adios");
		sleep(10);//Forzamos que el proceso hijo 'duerma' 10 segundos
		
	}
	else if (proc>0)//Si proc es positivo, se trata del proceso padre
	{
		puts(" soy el padre y me despido, adios");
		wait(NULL);//Hacemos que el padre espere a que el hijo acabe
	}
	else //si fork devuelve un valor negativo, ha ocurrido un error.
	{
		puts("Ha habido un error en el fork()");
	}
	return 0;
}
