#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    pid_t hijo=fork();

    if (hijo>0){
        wait(NULL);
    }
    else if (hijo==0)
    {
        execlp("bin/ps", "ps", "-l", "-e", NULL);
        printf("Diablaso Mamahuevo");
    }
    puts("Termino");
    return 0;
}
