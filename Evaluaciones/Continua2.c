#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <pthread.h>

int terminos = -1;
int *serie;
pthread_mutex_t lock;

int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int parImpar(int n){
    for (int i = 0; i < terminos; i++) {
        if (serie[i] % 2 == 0) {
            printf("Número %d: %d es par\n", i + 1, serie[i]);
        } else {
            printf("Número %d: %d es impar\n", i + 1, serie[i]);
        }
    }
}

void* hilo_con_mutex (void *arg){
    int input;
    printf("¿Cuántos términos de la serie?: ");
    scanf("%d", &input);

    pthread_mutex_lock(&lock); 
    terminos = input;
    pthread_mutex_unlock(&lock); 

    return NULL;
}

int main() {
    pthread_t hilo;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&hilo, NULL, &hilo_con_mutex, NULL);
    pthread_join(hilo, NULL);

    serie = (int *)malloc(terminos * sizeof(int));

    if (terminos <= 0) {
        printf("Cantidad no válida.\n");
        return 1;
    }
    
    printf("Calculando serie de %d términos...\n", terminos);
    for (int i = 0; i < terminos; i++) {
        serie[i] = fibonacci(i);
        printf("%d ", serie[i]);
    }
    printf("\n");

    parImpar(terminos);

    free(serie);
    pthread_mutex_destroy(&lock);
    return EXIT_SUCCESS;
}