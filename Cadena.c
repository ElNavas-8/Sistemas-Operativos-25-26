#include <stdio.h>
#include <limits.h>

int main()
{
    char cadena[]="Esta es una cadena en C";
    printf("Tamaño de un long int en C: %ld bytes \n", sizeof (long int));
    printf("Tamaño de un float en C: %ld bytes \n", sizeof (float));
    printf("Tamaño de mi cadena usando sizeof: %ld bytes \n", sizeof (cadena));
    printf("Tamaño de mi cadena usando strlen: %ld caracteres \n", strlen(cadena));

    return 0;
}