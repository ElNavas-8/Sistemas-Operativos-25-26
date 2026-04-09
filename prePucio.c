#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/mman.h>

#define N 10

int main() {
    int datos[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int *sumas = mmap(NULL, 2 * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
    if (sumas == MAP_FAILED){
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    
    pid_t son = fork();

    if (son < 0) {
        perror("Error en fork");
        munmap(sumas, sizeof(int));
        exit(EXIT_FAILURE);
    }

    int mitad = N/2;

    if (son == 0) { // --- PROCESO HIJO ---
        for(int i = mitad; i<N; i++){
            sumas[1] += datos[i];
        }
        printf("La suma total es %d\n", sumas[1]);

        printf("\n[Hijo] Finalizado.\n");
        exit(0);

    } else { // --- PROCESO PADRE ---
        for(int i = 0;i<mitad;i++){
            sumas[0] += datos[i];
        }
        printf("La suma total es %d\n", sumas[0]);

        wait(NULL);
        
        printf("[Padre] El hijo ha terminado. Sumando todo\n");
        printf("La suma total es %d\n", sumas[0]= sumas[0] + sumas[1]);
        munmap(sumas, sizeof(int));
    }

    return 0;
}