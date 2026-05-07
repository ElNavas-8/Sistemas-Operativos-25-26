#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <pthread.h>
#include <signal.h>

// Un programa que, da el pid varias veces y que tiene un contandor de veces necesarias para cerrar el proceso con crtl + c

// Otro programa que da cafe, tira el pid todo el rato. Pide moneda, kill -SIGUSR1 PID. Esto suma 1 de tres contador para dispensar cafe. 

static volatile sig_atomic_t contador = 0;

void insertar_moneda(int sig) {
    (void)sig;
    contador++;
    write(STDOUT_FILENO, "\n[SISTEMA] ¡Moneda detectada!\n", 30);
}

int main() {
    signal(SIGUSR1, insertar_moneda);

    pid_t pid = getpid();
    
    printf("=== MÁQUINA DE CAFÉ ===\n");
    printf("PID del proceso: %d\n", pid);
    printf("Precio: 3 monedas\n");
    printf("-----------------------\n");

    while (contador < 3) {
        printf("Esperando monedas... (Llevas %d/3). Mi PID es: %d\n", contador, pid);
        
        sleep(2);
    }

    printf("\n[MÁQUINA] ¡Pago completado! Preparando café...\n");
    printf("☕ ¡Aquí tienes tu café! Que tengas un buen día.\n");

    return 0;
}