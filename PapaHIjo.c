#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t proceso;
    int status;
    int numero = 7;

    // Error corregido: faltaba una coma en printf
    printf("Soy el padre (PID %d): voy a crear al hijo\n", getpid());

    proceso = fork();

    if (proceso < 0) { // Error corregido: evaluación de error del fork (era proceso=0)
        perror("Error del fork");
        exit(EXIT_FAILURE);
    } 
    else if (proceso == 0) {
        // --- Código del HIJO ---
        printf("Hijo, PID %d: evaluando si el numero %d es par o impar...\n", getpid(), numero);

        // Error corregido: "if n" no existe, y la sintaxis de exit requiere paréntesis
        if (numero % 2 == 0) {
            exit(0); // 0 significa PAR en nuestra lógica
        } else {
            exit(1); // 1 significa IMPAR
        }
    } 
    else {
        // --- Código del PADRE ---
        printf("Padre, PID %d: esperando a que mi hijo (PID %d) termine su tarea\n", getpid(), proceso);

        // Error corregido: faltaba punto y coma
        wait(&status);

        if (WIFEXITED(status)) {
            int resultado_hijo = WEXITSTATUS(status);
            
            // Error corregido: se usaba '=' (asignación) en vez de '==' (comparación)
            if (resultado_hijo == 0) {
                puts("El hijo ha acabado: El numero era PAR.");
            } else if (resultado_hijo == 1) {
                puts("El hijo ha acabado: El numero era IMPAR.");
            } else {
                puts("El hijo retorno un codigo desconocido.");
            }
        } else {
            puts("El hijo no termino normalmente.");
        }
    }

    return 0;
}
