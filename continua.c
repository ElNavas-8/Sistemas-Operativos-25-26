#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>  
#include <sys/wait.h>  

#define INCREMENTOS 100000
#define NUM_HIJOS 4

int main(void)
{
    // Creo la memoria compartida, mmap aparta un espacio de memoria que será heredado por los hijos
    int *memoria_compartida = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (memoria_compartida == MAP_FAILED) {
        perror("Error en mmap");
        exit(EXIT_FAILURE);
    }

    memoria_compartida[0] = 0; // Inicializo el memoria_compartida a 0

    // Creo los procesos hijos
    for (int i = 1; i <= NUM_HIJOS; i++) {
        pid_t pid_ = fork();

        if (pid_ < 0) {
            perror("Error en fork");
            exit(EXIT_FAILURE);
        }

        if (pid_ == 0) {
            // HIJO
            for (int i = 0; i < INCREMENTOS; i++) {
                (*memoria_compartida)++; // Incremento de memoria_compartida
            }
            
            exit(i); // Finaliza enviando su ID (1, 2, 3 o 4)
        }
    }

    // Recogemos a los hijos con wait
    int status;
    pid_t pid_id;
    
    printf("Esperando a los hijos...\n\n");

    for (int i = 1; i <= NUM_HIJOS; i++) {
        pid_id = wait(&status);

        if (WIFEXITED(status)) {
            int id_hijo = WEXITSTATUS(status);
            printf("El hijo con PID %d (ID interno: %d) ha terminado en la posición %d de finalización.\n", 
                    pid_id, id_hijo, i);
        }
    }

    // Mostramos el resultado del memoria_compartida
    printf("\n--- RESULTADOS ---\n");
    printf("Valor esperado: 400000\n");
    printf("Valor obtenido: %d\n", memoria_compartida[0]);
    printf("INCREMENTOS perdidos: %d\n", 400000-memoria_compartida[0]);

    // Liberarmos los recursos
    if (munmap(memoria_compartida, sizeof(int)) == -1) {
        perror("Error en munmap");
    }

    return 0;
}