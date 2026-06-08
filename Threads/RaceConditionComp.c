#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_HILOS 5
#define INCREMENTOS 1000000
#define VALOR_ESPERADO (NUM_HILOS * INCREMENTOS) // 500.000

long contador = 0;
pthread_mutex_t lock;

void* hilo_sin_mutex (void *arg){
    for (int i = 0; i<INCREMENTOS; i++){ 
        contador++;
    }
    return NULL;
}

void* hilo_con_mutex (void *arg){
    for (int i = 0; i<INCREMENTOS; i++){
        pthread_mutex_lock(&lock); 
        contador++;
        pthread_mutex_unlock(&lock); 
    }
    return NULL;
}

long ejecutar_prueba(void *(*funcion_hilo)(void*), const char *etiqueta){
    pthread_t hilos[NUM_HILOS];
    contador = 0;
    printf("\n[%s]\n", etiqueta);

    for (int i = 0; i<NUM_HILOS; i++){
        pthread_create(&hilos[i], NULL, funcion_hilo, NULL);
    }

    for (int i = 0; i<NUM_HILOS; i++){
        pthread_join(hilos[i], NULL);
    }
    
    printf("\n--- RESULTADOS ---\n");
    printf("Valor esperado: %ld\n", contador);
    printf("Valor obtenido: %d\n", VALOR_ESPERADO);
    printf("INCREMENTOS perdidos: %s\n", contador==VALOR_ESPERADO ? "Correcto" : "Incorrecto(race condition)");

}

int main (void){
    pthread_mutex_init(&lock, NULL);

    ejecutar_prueba(hilo_sin_mutex, "SIN MUTEX");

    ejecutar_prueba(hilo_con_mutex, "CON MUTEX");

    pthread_mutex_destroy(&lock);
    return EXIT_SUCCESS;
}