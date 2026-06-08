#include <stdio.h>
sum(int a, int b);

int main(void)
{   
    int var1 = -1, var2 = 2; 
    char var[]= "Hola Mundo";

    printf("var1 = %i, var2 = %u var1+var2 = %i\n", var1, var2, sum(var1, var2));
    printf("%s\n", var);
    
    return 0;
}

int sum(int a, int b)
{
    return a + b;
}