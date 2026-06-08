#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t hijo;

    hijo = fork();

    if (hijo > 0) {
        wait (NULL);
        puts ("Tiene que tener fe, ellos no tienen fe. Ya nadie tiene fe, asi vida deja de tener sentido.");
    } else if (hijo == 0) {
        execlp("./escritor", "escritor", NULL);
        puts("La zona no los hubiera dejado llegar tan lejos.");
    }
}