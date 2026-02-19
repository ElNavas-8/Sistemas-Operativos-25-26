#include <stdio.h>

int main (void)
{
    int myNumbers[4]= {323, 32, 32, 32};

    printf("%p\n", myNumbers);
    printf("%p\n", &myNumbers[0]);
    printf("%d\n", *myNumbers);

    return 0;
}