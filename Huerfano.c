#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error al crear el hijo");
        exit(1);
    }

    if (pid == 0) {
        printf("Hijo: Mi PID es %d y mi padre inicial es %d\n", getpid(), getppid());
        
        printf("Hijo: Durmiendo 10 segundos esperando a que mi padre muera...\n");
        sleep(10);
        
        printf("\nHijo: He despertado. Mi nuevo padre (PPID) es: %d\n", getppid());
        printf("Hijo: Terminando proceso.\n");
    } else {
        printf("Padre: Mi PID es %d y voy a morir ahora mismo.\n", getpid());
        exit(0); 
    }

    return 0;
}
