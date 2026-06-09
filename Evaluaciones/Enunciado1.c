#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define ROWS 3
#define COLS 3

int matrix[ROWS][COLS];
int buffer_temporal;
int fila_actual = 0, col_actual = 0; // Para que el Filtro sepa dónde escribir

pthread_t Coordinador, Lector, Filtro; 

// Handlers vacíos (solo sirven para interrumpir el pause)
void coordinador_call(int sig){}
void lector_call(int sig){}
void filtro_call(int sig){}

void imprimir_resultado(){
    printf("\nMatriz resultante:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// HILO A: EL CEREBRO
void* coordinador_function(){
    // El Coordinador gestiona el avance celda por celda
    for (fila_actual = 0; fila_actual < ROWS; fila_actual++) {
        for (col_actual = 0; col_actual < COLS; col_actual++) {
            
            // 1. Inicia el ciclo avisando al Lector
            pthread_kill(Lector, SIGUSR2);
            
            // 2. Espera a que el Filtro termine esta celda específica
            pause(); 
        }
    }
    
    // Una vez llena, imprime y limpia
    imprimir_resultado();
    pthread_cancel(Filtro);
    pthread_cancel(Lector);
    pthread_exit(NULL);
}

// HILO B: EL INPUT
void* lector_function(){
    while(1){
        pause(); // Espera la orden del Coordinador
        
        printf("Ingrese un número para la posición [%d][%d]: ", fila_actual, col_actual);
        scanf("%d", &buffer_temporal);
        
        // Pasa el testigo al Filtro
        pthread_kill(Filtro, SIGALRM); 
    }
    return NULL;
}

// HILO C: EL TRABAJADOR
void* filtro_function(){
    while(1){ 
        pause(); // Espera el número del Lector
        
        // Escribe en la posición actual gestionada por el Coordinador
        if(buffer_temporal % 2 == 0){
            matrix[fila_actual][col_actual] = 1;
        } else {
            matrix[fila_actual][col_actual] = 0;
        }
        
        // Avisa al Coordinador de que la celda está lista
        pthread_kill(Coordinador, SIGUSR1);
    }
    return NULL;
}

int main(void){
    // Registro de señales
    signal(SIGUSR1, coordinador_call);
    signal(SIGUSR2, lector_call);
    signal(SIGALRM, filtro_call);

    // Creación de hilos
    pthread_create(&Lector, NULL, &lector_function, NULL);
    pthread_create(&Filtro, NULL, &filtro_function, NULL);
    // El coordinador se crea el último para dar tiempo a los demás a hacer su primer pause()
    pthread_create(&Coordinador, NULL, &coordinador_function, NULL);

    pthread_join(Coordinador, NULL);
    pthread_join(Lector, NULL);
    pthread_join(Filtro, NULL);
    
    return 0;
}