#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/mman.h>

int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int *terminos = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
    *terminos = -1;

    pid_t son = fork();

    if (son < 0) {
        perror("Error en fork");
        return 1;
    }

    if (son == 0) { // --- PROCESO HIJO ---
        while(*terminos == -1) {
            usleep(100); 
        }

        printf("[Hijo] Calculando serie de %d términos...\n", *terminos);
        for (int i = 0; i < *terminos; i++) {
            printf("%d ", fibonacci(i));
        }
        printf("\n[Hijo] Finalizado.\n");
        exit(0);

    } else { // --- PROCESO PADRE ---
        printf("[Padre] ¿Cuántos términos de la serie?: ");
        int input;
        scanf("%d", &input);
        
        *terminos = input;

        wait(NULL);
        printf("[Padre] El hijo ha terminado. Liberando memoria...\n");
        munmap(terminos, sizeof(int));
    }

    return 0;
}