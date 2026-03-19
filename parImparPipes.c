#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int tuberia[2];
    int tuberia2[2];
    
    pid_t hijo;

    int r[10];

    if (pipe(tuberia) == -1 || pipe(tuberia2) == -1) {
        perror("Pipe failed");
        return 1;
    }

    hijo = fork();

    if (hijo > 0) { 
        close(tuberia[0]);
        close(tuberia2[1]);

        printf("[PADRE] Dice: ");

        for(int i=0; i<sizeof(r)/sizeof(r[0]); i++) {
            r[i] = rand()%100 + 1;
            printf("%d ", r[i]);
        }

        write(tuberia[1], r, sizeof(r));        
        
        close(tuberia[1]);
        close(tuberia2[0]);
        wait(NULL);



    } else if (hijo == 0) { 
        close(tuberia[1]); 
        close(tuberia2[0]);

        read(tuberia[0], r, sizeof(r)); 

        printf("[HIJO] He recibido los siguientes números:\n");
        for (int i = 0; i < 10; i++) {
            if (r[i] % 2 == 0) {
                printf("Número %d: %d es par\n", i + 1, r[i]);
            } else {
                printf("Número %d: %d es impar\n", i + 1, r[i]);
            }
            printf("Número %d: %d\n", i + 1, r[i]);
        }

        write(tuberia2[1], r, sizeof(r));

        close(tuberia[0]);
        close (tuberia2[1]);
        exit(0);
    }
    
    return 0;
}