#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>

/* Creamos 3 procesos, el que lee y el que escribe; y el padre. 
Tenemos una variable compartida con un valor. 
El proceso lee va a leer un numero por teclado. 
Una vez que el proceso lee ha leido el numero, el proceso escribe, accede a la var compartida y muestra el numero por pantalla. 
A continuacion mostrara "pulse una tecla para tecnica". 
En ese momento muere el proceso lee, escribe y padre. */

#define N 1000000

int main() {

    sem_t *semaphore = sem_open("/mi semaforo", O_CREAT, S_IRUSR | S_IWUSR, 1);

    int *sumas = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *sumas = 0;
    
    pid_t son = fork();

    if (son == 0) { // --- PROCESO HIJO ---
        for(int i = 0; i < N; i++){
            sem_wait(semaphore);
            *sumas = *sumas + 1;
            sem_post(semaphore);
        }
        exit(0);

    } else { // --- PROCESO PADRE ---
        for(int i = 0; i<N; i++){
            sem_wait(semaphore);
            *sumas = *sumas - 1;
            sem_post(semaphore);
        }
    }
    wait(NULL);
    printf("La suma total es %d\n", *sumas);
    munmap(sumas, sizeof(int));
    sem_close(semaphore);
    sem_unlink("/mi semaforo");

    return 0;
}