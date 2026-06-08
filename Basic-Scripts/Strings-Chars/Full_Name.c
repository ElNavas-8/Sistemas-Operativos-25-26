#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define SIZE 256

int main()
{
    char nombre[SIZE];
    
    printf("escribe tu nombre y apellidos");
    fgets(nombre, SIZE, stdin);

    if ((strlen(nombre)>0) && nombre [strlen(nombre)-1]=='\n')
    {
        nombre[strlen(nombre)-1]='\0';
    }

    printf("Hola %s, igual hasta acabas aprobando Sistemas Operativos\n", nombre);
    return 0;
}