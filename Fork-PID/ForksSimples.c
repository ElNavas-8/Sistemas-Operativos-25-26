#include <stdio.h>
#include <unistd.h>

int main ()
{
    printf("Ey que pasa");
    fork();
    puts("Hola mundo");
    fork();
    fork(); 
    puts("Adios");

    return 0;
}