#include <stdio.h>
#include <string.h>

int main (void){

    char str1[12] = "Pene";
    char str2[12] = "Sucio";
    char str3[12];

    strcpy(str3, str1);
    printf("strcpy(str1, str2) = %s\n", str3);
    
    int length = strlen(str1);
    printf("strlen(str1) = %d\n", length);

    str1[length] = ' ';
    str1[length + 1] = '\0';
    strcat(str1, str2);
    printf("strcat(str1, str2) = %s\n", str1);
}