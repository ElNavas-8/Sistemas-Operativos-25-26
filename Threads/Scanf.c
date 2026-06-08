#include <stdio.h>

sum(int a, int b);

int main(void)
{   
    int var1 , var2;

    puts("Ingrese el primer numero: ");
    scanf("%i", &var1);
    puts("Ingrese el segundo numero: ");
    scanf("%i", &var2);

    printf("a = %i, b = %u a + b = %i\n", var1, var2, sum(var1, var2));
    printf("El numero %i es par? %i\n", sum(var1, var2), even(sum(var1, var2)));
    printf("El numero %i es primo? %i\n", sum(var1, var2), prime(sum(var1, var2)));

    return 0;
}

int sum(int a, int b)
{
    return a + b;
}

int even(int a)
{
    if (a % 2 == 0) { 
        return 1; 
    }
    else {
        return 0;
    }
}

int prime (int a)
{
    if (a <= 1) {
        return 0;
    }
    for (int i = 2; i < a; i++) {
        if (a % i == 0) {
            return 0;
        }
    }
    return 1;
}