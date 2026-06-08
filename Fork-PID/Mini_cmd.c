#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int valor;

    while (1){
        printf("Ingresa un valor ");
        
        if(scanf("%d", &valor) != 1) break;
        if (valor == -1)break;

        pid_t pid = fork();

        if (pid < 0) {
            perror("error");
        } else if (pid == 0) {
            if (valor == 0) {
                execlp("ls", "ls", NULL);
            } else if (valor == 1) {
                execlp("ps", "ps", NULL);
            } else if (valor == 2) {
                execlp("pwd", "pwd", NULL);
            } else {
                printf("Opción no válida.\n");
                exit(0);
            }
            perror("Error al ejecutar el comando");
            exit(1);
        } else {
            wait(NULL);
        }
    }
    printf("Programa finalizado.\n");
    return 0;
}