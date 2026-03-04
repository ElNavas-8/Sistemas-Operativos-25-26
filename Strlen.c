#include <stdio.h>
#include <string.h>

int mi_strlen(char*);

int main()
{
    char cadena[150];
    
    puts("Introduce una cadena");
    fgets(cadena, sizeof(cadena), stdin);
    printf("La longitud de la cadena es %d caracteres \n", mi_strlen(cadena));

    return 0;
}

int mi_strlen(char *str) 
{
    char *p = str;
    
    while (*p != '\0') 
        p++;
    }
    
    return p - str;
}