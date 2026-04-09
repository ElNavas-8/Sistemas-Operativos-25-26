#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/mman.h>

#define N 1000000
#define M 1000000

int main() {

    int *sumas = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *sumas = 0;
    
    pid_t son = fork();

    if (son == 0) { // --- PROCESO HIJO ---
        for(int i = 0; i < N; i++){
            *sumas = *sumas + 1;
        }
        exit(0);

    } else { // --- PROCESO PADRE ---
        for(int i = 0; i<M; i++){
            *sumas = *sumas - 1;
        }
    }
    wait(NULL);
    printf("La suma total es %d\n", *sumas);
    munmap(sumas, sizeof(int));

    return 0;
}