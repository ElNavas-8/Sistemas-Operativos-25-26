#include <stdio.h>

int main (void){
    int number, invertedNumber =0;
    printf("Enter a number: ");
    scanf("%d", &number);

    while (number != 0 ){
        int lastDigit = number % 10;
        invertedNumber = invertedNumber * 10 + lastDigit;
        number /= 10; 
    }
    printf("The inverted number is: %d\n", invertedNumber);
    return 0;
}