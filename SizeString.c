#include <stdio.h>
#include <string.h>

int main (void){
    char string[100];
    printf("Enter a string: ");
    fgets(string, sizeof(string), stdin);
    int size = strlen(string) - 1;
    printf("The size of the string is: %d\n", size);
}