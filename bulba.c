#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

#define LIMITE 5

pthread_t array[LIMITE];

void calcula() {
    long long unsigned t;
    for (t = 0; t < (0xFFFFFFF); t++); 
}

void crearHilos(int n) {
    if (n >= LIMITE) return;

    int* id = malloc(sizeof(int));
    *id = n;
    
    printf("[ID: %lu] Creando hilo %d en la pila\n", pthread_self(), n);
    pthread_create(&array[n], NULL, calcula, id);

    crearHilos(n + 1);

    pthread_join(array[n], NULL);
    printf("[ID: %lu] Hilo %d ha muerto.\n", pthread_self(), n);
}

int main() {
    printf("Iniciando creación recursiva de %d hilos...\n", LIMITE);
    
    crearHilos(0);

    printf("Todos los hilos han sido procesados. Fin del programa.\n");
    return 0;
}