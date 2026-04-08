#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/mman.h>

unsigned long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// Usamos un puntero para la memoria compartida
static int *number;

int main() {
    int fd[2];

    unsigned long long resultado_final; 

    if (pipe(fd) == -1) return 1;

    number = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *number = 0; 

    pid_t son = fork();

    if (son == 0) { // Proceso HIJO
        close(fd[0]); 
        
        while(*number == 0) {usleep(2);}

        unsigned long long resultado = factorial(*number);

        write(fd[1], &resultado, sizeof(unsigned long long));
        
        close(fd[1]);
        exit(0);

    } else if (son > 0) { // Proceso PADRE
        close(fd[1]); 

        printf("Dame un valor para la variable: ");
        scanf("%d", number); 
        

        read(fd[0], &resultado_final, sizeof(unsigned long long));
        
        printf("Padre: El factorial de %d es %llu\n", *number, resultado_final);
        
        close(fd[0]);
        wait(NULL); 
        munmap(number, sizeof(int));
    }
    
    return 0;
}
