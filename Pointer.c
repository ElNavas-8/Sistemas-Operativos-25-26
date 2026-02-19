#include <stdio.h>

int main (void)
{
    int myNumbers[4]= {323, 32, 255, 795};
    int i;
    int *ptr=myNumbers;

    printf("%p\n", myNumbers);
    printf("%p\n", &myNumbers[0]);
    printf("%p\n", &myNumbers[1]);
    printf("%i\n", *myNumbers);
    
    for (i=0;i<4;i++)
    {
        printf("%i y %i\n", *(ptr++), myNumbers);
    }
    printf(%p\n, ptr)

    return 0;
}