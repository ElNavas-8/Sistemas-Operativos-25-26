#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {

    int tuberia[2];
    pid_t hijo;
    
    int input1, input2;

    if (pipe(tuberia) == -1) {
        perror("Pipe failed");
        return 1;
    }

    hijo = fork();

    if (hijo > 0) { 
        close(tuberia[0]);

        printf("[PADRE] Ingresa primer Nº: ");
        scanf("%d", &input1);
        write(tuberia[1], &input1, sizeof(input1));

        printf("[PADRE] Ingresa el segundo Nº: ");
        scanf("%d", &input2);
        write(tuberia[1], &input2, sizeof(input2));

        close(tuberia[1]); 
        wait(NULL);        
        printf("[PADRE] El hijo ha terminado.\n");

    } else if (hijo == 0) { 
        close(tuberia[1]);

            read(tuberia[0], &input1, sizeof(input1));
            read(tuberia[0], &input2, sizeof(input2));

            printf("[HIJO] El primer número es: %d\n", input1);
            printf("[HIJO] El segundo número es: %d\n", input2);
            printf("[HIJO] La suma total es: %d\n", input1 + input2);

            close(tuberia[0]);
            exit(0);
    }
    
    return 0;
}