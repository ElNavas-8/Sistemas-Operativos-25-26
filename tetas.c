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
A continuacion mostrara "pulse una tecla para terminar". 
En ese momento muere el proceso lee, escribe y padre. */


int main() {

    int *variable_compartida = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_t *semaphore = sem_open("/mi semaforo", O_CREAT, S_IRUSR | S_IWUSR, 0);

    pid_t lee = fork();

    if (lee == 0) { // --- PROCESO HIJO ---
        printf("Introduce un numero: ");
        scanf("%d", variable_compartida);
        sem_post(semaphore);
        exit(0);
    } 

    pid_t escribe = fork();

    if (escribe == 0) { // --- PROCESO HIJO ---
        sem_wait(semaphore);
        printf("El numero es %d\n", *variable_compartida);
        
        printf("Pulse una tecla para terminar\n");
        scanf("%*c");
        
        exit(0);
    }

    wait(NULL);
    wait(NULL); // --- IGNORE ---

    munmap(variable_compartida, sizeof(int));
    sem_close(semaphore);
    sem_unlink("/mi semaforo");

    return 0;
}