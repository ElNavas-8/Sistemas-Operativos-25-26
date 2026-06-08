#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1000000
int variable_compartida;
pthread_t suma, resta;
pthread_mutex_t lock;

void func_sum(void* arg){
    for (int i = 0; i<N; i++){
        pthread_mutex_lock(&lock); 
        variable_compartida++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void func_minus(void* arg){
    for (int i = 0; i<N; i++){
        pthread_mutex_lock(&lock); 
        variable_compartida--;
        pthread_mutex_unlock(&lock); 
    }
    return NULL;
}

int main (void){
    variable_compartida = 0;
    
    pthread_mutex_init(&lock, NULL);

    pthread_create(&suma, NULL, &func_sum, NULL); // se crea el hilo, de ahi se le asigna una funcion, el hilo procedera a ejecutar la funcion
    pthread_create(&resta, NULL, &func_minus, NULL);

    pthread_join(suma, NULL);
    pthread_join(resta, NULL);

    printf("Resultadin: %d\n", variable_compartida);

    pthread_mutex_destroy(&lock);

    return 0;
}