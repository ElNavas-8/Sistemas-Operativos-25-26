#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <pthread.h>
#include <signal.h>

// Un programa que, da el pid varias veces y que tiene un contandor de veces necesarias para cerrar el proceso con crtl + c

// Otro programa que da cafe, tira el pid todo el rato. Pide moneda, kill -SIGUSR1 PID. Esto suma 1 de tres monedas para dispensar cafe. 

static volatile sig_atomic_t contador = 0;

void handle_sigint(int sig) {
    (void)sig;
    contador++;
    write(STDOUT_FILENO, "\nSeñal recibida\n", 17);
}

int main() {
    signal(SIGINT, handle_sigint);
    pid_t pid = getpid();
    int ultimo_valor = 0;

    printf("Iniciando programa. Ctrl + C para cerrar\n");

    while (contador < 3) {
        if (contador > ultimo_valor) {
            printf("El programa se resiste (%d de 3 intentos)...\n", contador);
            ultimo_valor = contador;
        }

        printf("[PID: %d]\n", pid);
        sleep(2); 
    }

    printf("\nCerrando programa...\n");
    return 0;
}