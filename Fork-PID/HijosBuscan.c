#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TAMANO 10

int main() {
    int array[TAMANO] = {10, 25, 34, 47, 52, 68, 71, 89, 93, 100};
    int objetivo = 71; // El número que queremos buscar
    int mitad = TAMANO / 2;
    pid_t hijo1, hijo2;
    int estado;

    printf("Padre (PID %d): Buscando el numero %d en el array...\n", getpid(), objetivo);

    // --- CREACIÓN DEL PRIMER HIJO ---
    hijo1 = fork();
    if (hijo1 < 0) {
        perror("Error en fork 1");
        exit(1);
    }

    if (hijo1 == 0) {
        // Lógica Hijo 1: Primera mitad (índices 0 a mitad-1)
        for (int i = 0; i < mitad; i++) {
            if (array[i] == objetivo) {
                printf("Hijo 1 (PID %d): ¡Encontrado en indice %d!\n", getpid(), i);
                exit(1); // Éxito
            }
        }
        exit(0); // Fracaso
    }

    // --- CREACIÓN DEL SEGUNDO HIJO ---
    hijo2 = fork();
    if (hijo2 < 0) {
        perror("Error en fork 2");
        exit(1);
    }

    if (hijo2 == 0) {
        // Lógica Hijo 2: Segunda mitad (índices mitad a TAMANO-1)
        for (int i = mitad; i < TAMANO; i++) {
            if (array[i] == objetivo) {
                printf("Hijo 2 (PID %d): ¡Encontrado en indice %d!\n", getpid(), i);
                exit(1); // Éxito
            }
        }
        exit(0); // Fracaso
    }

    // --- LÓGICA DEL PADRE ---
    // El padre debe esperar a AMBOS hijos
    for (int i = 0; i < 2; i++) {
        pid_t pid_finalizado = wait(&estado);

        if (WIFEXITED(estado)) {
            int resultado = WEXITSTATUS(estado);
            if (resultado == 1) {
                printf("Padre: El hijo %d encontro el numero.\n", pid_finalizado);
            } else {
                printf("Padre: El hijo %d NO encontro nada.\n", pid_finalizado);
            }
        }
    }

    printf("Padre: Tarea finalizada.\n");
    return 0;
}
