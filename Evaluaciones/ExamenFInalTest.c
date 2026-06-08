#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#define ROWS 4
#define COLS 3

// a) Estructura de datos global
int matrix[ROWS][COLS];
int ipos, jpos; // Comparten la posición actual del bucle

// Identificadores de los hilos
pthread_t positivo, negativo, coordinador_thread;

// Prototipos de funciones
void muestra_tabular();
void positivo_handler(int sig);
void negativo_handler(int sig);
void coordinador_handler(int sig);
void* positivo_f(void* arg);
void* negativo_f(void* arg);
void* coordinador_thread_f(void* arg);

// --- MANEJADORES DE SEÑALES ---
// Los manejadores pueden estar vacíos; su único propósito es interrumpir el 'pause()'
void positivo_handler(int sig) {}
void negativo_handler(int sig) {}
void coordinador_handler(int sig) {}

// b) e) Hilo Positivo
void* positivo_f(void* arg) {
    int input;
    while (1) {
        pause(); // Espera a que el coordinador le mande SIGUSR1
        
        printf("[Hilo POSITIVO] Asignar Valor a [%d][%d]: ", ipos, jpos);
        if (scanf("%d", &input) != 1) {
            printf("Error en la lectura.\n");
        }
        matrix[ipos][jpos] = input;

        // Avisa al coordinador que ya terminó su tarea
        pthread_kill(coordinador_thread, SIGALRM);
    }
    return NULL;
}

// b) e) Hilo Negativo
void* negativo_f(void* arg) {
    int input;
    while (1) {
        pause(); // Espera a que el coordinador le mande SIGUSR2
        
        printf("[Hilo NEGATIVO] Asignar Valor a [%d][%d]: ", ipos, jpos);
        if (scanf("%d", &input) != 1) {
            printf("Error en la lectura.\n");
        }
        matrix[ipos][jpos] = input;

        // Avisa al coordinador que ya terminó su tarea
        pthread_kill(coordinador_thread, SIGALRM);
    }
    return NULL;
}

// b) c) d) e) Hilo Coordinador
void* coordinador_thread_f(void* arg) {
    // Recorremos la matriz coordenando los turnos
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            ipos = i; // Guardamos la posición en las variables globales
            jpos = j;

            // d) Distribución de trabajo según el producto de índices
            if ((i * j) % 2 == 0) {
                // Producto par (o cero) -> Le toca al hilo positivo
                pthread_kill(positivo, SIGUSR1);
            } else {
                // Producto impar -> Le toca al hilo negativo
                pthread_kill(negativo, SIGUSR2);
            }

            // El coordinador se duerme hasta que el trabajador le devuelva el control
            pause(); 
        }
    }

    // f) Mostrar resultado en formato tabular
    muestra_tabular();

    // g) Finalización ordenada
    printf("\n[Coordinador] Eliminando hilo negativo...\n");
    pthread_cancel(negativo);
    pthread_join(negativo, NULL);

    printf("[Coordinador] Eliminando hilo positivo...\n");
    pthread_cancel(positivo);
    pthread_join(positivo, NULL);

    printf("[Coordinador] Finalizándose a sí mismo...\n");
    return NULL; 
}

// f) Función para mostrar la matriz
void muestra_tabular() {
    printf("\n--- MATRIZ RESULTANTE EN FORMATO TABULAR ---\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("--------------------------------------------\n");
}

// h) Hilo principal del programa
int main() {
    // Registrar los manejadores de señales en el sistema
    signal(SIGUSR1, positivo_handler);
    signal(SIGUSR2, negativo_handler);
    signal(SIGALRM, coordinador_handler);

    // Crear los hilos trabajadores primero
    pthread_create(&positivo, NULL, positivo_f, NULL);
    pthread_create(&negativo, NULL, negativo_f, NULL);

    // Un pequeño respiro para asegurar que los trabajadores ya estén ejecutando sus 'pause()'
    sleep(1);

    // Crear el hilo coordinador que comenzará a orquestar todo
    pthread_create(&coordinador_thread, NULL, coordinador_thread_f, NULL);

    // Esperar a que el coordinador haga todo su trabajo y se elimine
    pthread_join(coordinador_thread, NULL);

    printf("[Main] Todos los hilos han terminado. Cerrando programa de forma segura.\n");
    return EXIT_SUCCESS;
}