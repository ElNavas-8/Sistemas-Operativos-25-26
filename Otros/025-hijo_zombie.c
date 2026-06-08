#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/types.h>

int main (void)
{
	pid_t pid;
	printf("Soy el proceso padre y mi id es %d\n", getpid());
	if ((pid=fork())<0)
	{
		perror("Error al crear el proceso\n");
		exit(-1);
	}
	else if (pid>0)
	{
		sleep(1);
		exit(0);
	}
	else if(pid==0)
	{
		printf("Soy el hijo, con ID %d y padre %d\n", getpid(), getppid());
		sleep(3);
		printf("Soy el hijo, con ID %d y padre %d\n", getpid(), getppid());
		sleep(200);
		exit(0);
	}
	return 0;
}
