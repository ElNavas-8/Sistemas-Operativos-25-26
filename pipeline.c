#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int tuberia[2];

    pid_t hijo;

    char mensaje[] = "Chau pendejos";
    char buffer[100];

    pipe(tuberia);

    hijo = fork();

    if(hijo > 0){
        close(tuberia[0]);
        printf("[PADRE] escribe en el pipe\n");
        
        write(tuberia[1], mensaje, sizeof(mensaje));
        close(tuberia[1]);
        wait(NULL);
        puts("Mamhuevo subale a esa mierda caballero.");
    } else if (hijo == 0) {
        close(tuberia[1]);
        read(tuberia[0], buffer, sizeof(buffer));
        printf("[HIJO] recibe mesaje de su padre: %s\n", buffer);
        close(tuberia[0]);
        exit(1);
    }
}