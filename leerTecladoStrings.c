#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main() {

    int tuberia[2];
    int tuberia2[2];
    pid_t hijo;
    
    char input1[100];
    int charcount = 0;

    if (pipe(tuberia) == -1 || pipe(tuberia2) == -1) {
        perror("Pipe failed");
        return 1;
    }

    hijo = fork();

    if (hijo > 0) { 
        close(tuberia[0]);
        close(tuberia2[1]);

        printf("[PADRE] Dice: ");
        fgets(input1, sizeof(input1), stdin);
        input1[strcspn(input1, "\n")] = 0;


        write(tuberia[1], input1, sizeof(input1));        
        
        read(tuberia2[0], &charcount, sizeof(charcount));
        printf("[PADRE] Número de vocales: %d\n", charcount);

        wait(NULL);

        close(tuberia[0]);
        close(tuberia2[1]);

    } else if (hijo == 0) { 
        close(tuberia[1]);
        close(tuberia2[0]);

            read(tuberia[0], input1, sizeof(input1)); 

            for(int i=0; input1[i]; i++) {
                char c = tolower(input1[i]);
                if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                    charcount ++;
                }
            }

            printf("[HIJO] Dice: %s\n", input1);

            write(tuberia2[1], &charcount, sizeof(charcount));

            close(tuberia[0]);
            close(tuberia2[1]);
            exit(0);
    }
    
    return 0;
}