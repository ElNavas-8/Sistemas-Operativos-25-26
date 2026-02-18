#include <stdio.h>

sum(int a, int b);

int main(void)
{   
    int var1 , var2;

    puts("Ingrese el primer numero: ");
    scanf("%i", &var1);
    puts("Ingrese el segundo numero: ");
    scanf("%i", &var2);

    printf("a = %i, b = %u a+b = %i\n", var1, var2, sum(var1, var2));
    
    return 0;
}

int sum(int a, int b)
{
    return a + b;
}