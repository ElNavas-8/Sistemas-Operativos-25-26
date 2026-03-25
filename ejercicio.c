#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main() {
    int pipe1[2];
    int pipe2[2]; 
    pid_t pid;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Error al crear las tuberías");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("Error en el fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pipe1[1]); 
        close(pipe2[0]);

        int numeros[10];
        int suma = 0;
        int pares = 0;

        read(pipe1[0], numeros, sizeof(numeros));

        for (int i = 0; i < 10; i++) {
            suma += numeros[i];
            if (numeros[i] % 2 == 0) {
                pares++;
            }
        }

        write(pipe2[1], &suma, sizeof(suma));

        close(pipe1[0]);
        close(pipe2[1]);

        exit(pares);

    } else {
        close(pipe1[0]);
        close(pipe2[1]);

        int numeros[10];
        int suma_recibida;
        int status;

        srand(time(NULL));
        printf("Padre: Array generado -> ");
        for (int i = 0; i < 10; i++) {
            numeros[i] = rand() % 100;
            printf("%d ", numeros[i]);
        }
        printf("\n");

        write(pipe1[1], numeros, sizeof(numeros));

        read(pipe2[0], &suma_recibida, sizeof(suma_recibida));

        wait(&status);

        if (WIFEXITED(status)) {
            int cantidad_pares = WEXITSTATUS(status);
            
            printf("Padre: La suma calculada por el Hijo es: %d\n", suma_recibida);
            printf("Padre: El Hijo terminó con éxito y procesó %d números pares.\n", cantidad_pares);
        } else {
            printf("Padre: El Hijo no terminó de forma normal.\n");
        }

        close(pipe1[1]);
        close(pipe2[0]);
    }

    return 0;
}