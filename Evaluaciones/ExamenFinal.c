#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define REPETICIONES 6
#define NUMEROS_POR_INTERRUPCION 1

pthread_t productor, escritor;
sem_t sem_productor, sem_escritor;

int digito_aleatorio = 0;
static volatile sig_atomic_t contador = 0;

// Manejador de Ctrl+C (SIGINT)
void productor_handler(int sig){
    (void)sig;
    contador++;
    
    if (contador < REPETICIONES) {
        write(STDOUT_FILENO, "\n[SISTEMA] ¡Input detectado! Generando números...\n", 50);
        sem_post(&sem_productor); // Despierta al productor para iniciar la tanda
    } else {
        write(STDOUT_FILENO, "\n[SISTEMA] Límite alcanzado. Saliendo...\n", 41);
        // Despertamos a los hilos para que vean que contador == REPETICIONES y terminen
        sem_post(&sem_productor);
        sem_post(&sem_escritor);
    }
}

void* productor_f(void* arg){
    (void)arg;
    // Inicializar la semilla para números aleatorios en este hilo
    srand(time(NULL));

    while(contador < REPETICIONES){
        // Espera a que ocurra un Ctrl+C
        sem_wait(&sem_productor);
        
        // Si el Ctrl+C fue el sexto, salimos del bucle
        if(contador >= REPETICIONES) break;

        // Genera 5 números (uno a uno, coordinado con el escritor)
        for(int i = 0; i < NUMEROS_POR_INTERRUPCION; i++){
            digito_aleatorio = rand() % 1000 + 1; // Número aleatorio entre 1 y 1000
            sem_post(&sem_escritor);        // Le avisa al escritor que ya hay número
            
            // Espera un momento (o un semáforo de feedback) para no sobreescribir 
            // el número antes de que el escritor lo lea.
            usleep(10000); // 10 milisegundos de cortesía para sincronía pasiva
        }
    }
    return NULL;
}

void* escritor_f(void* arg){
    (void)arg;
    int total_impresos = 0;

    while(contador < REPETICIONES){
        // Espera a que el productor genere un número
        sem_wait(&sem_escritor);
        
        if(contador >= REPETICIONES) break;

        total_impresos++;
        printf("[%d] Numero Generado es: %d\n", total_impresos, digito_aleatorio);
        fflush(stdout); // Asegura que se muestre en pantalla inmediatamente
    }
    return NULL;
}

int main(void){
    // Configurar la señal SIGINT (Ctrl+C)
    signal(SIGINT, productor_handler); // [cite: 3]
    
    // Inicializar semáforos en 0 (empiezan bloqueados)
    sem_init(&sem_productor, 0, 0);
    sem_init(&sem_escritor, 0, 0);

    // Crear los hilos
    pthread_create(&productor, NULL, productor_f, NULL); //[cite: 4]
    pthread_create(&escritor, NULL, escritor_f, NULL); //[cite: 4]
    
    // Esperar a que los hilos terminen (ocurrirá cuando contador llegue a REPETICIONES)
    pthread_join(productor, NULL); //[cite: 4]
    pthread_join(escritor, NULL); //[cite: 5]
    
    // Limpieza de recursos al final del programa
    sem_destroy(&sem_escritor); //[cite: 4]
    sem_destroy(&sem_productor); //[cite: 4]
    
    printf("Programa finalizado correctamente.\n");
    return 0;
}