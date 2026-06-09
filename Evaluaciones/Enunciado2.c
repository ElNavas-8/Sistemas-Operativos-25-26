#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_HILOS 3
#define ESPACIOS 5

pthread_mutex_t mutex;
int suma_total = 0, datos[ESPACIOS];
sem_t semaforo; // Corregido: Variable normal, no puntero

void* thread_function(void* arg) {
    sem_wait(&semaforo); // Espera la señal del hilo principal del hijo
    
    for (int i = 0; i < ESPACIOS; i++) {
        pthread_mutex_lock(&mutex);
        suma_total += datos[i];
        pthread_mutex_unlock(&mutex);
        usleep(10000);
    }
    pthread_exit(NULL);
}

int main() {
    int tuberia[2];

    // 1. Crear la tubería antes del fork
    if (pipe(tuberia) == -1) {
        perror("Error al crear el pipe");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Error al crear el proceso hijo");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        // --- HIJO ---
        close(tuberia[1]); // Cierra escritura

        read(tuberia[0], datos, sizeof(datos)); // sizeof(datos) es suficiente
        close(tuberia[0]);

        pthread_mutex_init(&mutex, NULL);
        sem_init(&semaforo, 0, 0); // Inicializado en 0 (bloqueado)

        pthread_t hilos[NUM_HILOS];
        for (int i = 0; i < NUM_HILOS; i++) {
            pthread_create(&hilos[i], NULL, thread_function, NULL);
        }

        // Liberar hilos
        for (int i = 0; i < NUM_HILOS; i++) {
            sem_post(&semaforo);
        }

        for (int i = 0; i < NUM_HILOS; i++) {
            pthread_join(hilos[i], NULL);
        }

        printf("[Hijo] La suma total es: %d\n", suma_total);
        
        pthread_mutex_destroy(&mutex);
        sem_destroy(&semaforo);

        exit(77); // Fin con código 77

    } else {
        // --- PADRE ---
        close(tuberia[0]); // Cierra lectura
        
        int array[] = {10, 20, 30, 40, 50};

        // 2. CORRECCIÓN: sizeof(array) es el tamaño correcto
        write(tuberia[1], array, sizeof(array)); 
        close(tuberia[1]);

        int status;
        wait(&status); // Espera al hijo

        if (WIFEXITED(status)) {
            printf("[Padre] El hijo terminó con código: %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}