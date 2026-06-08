#include <stdio.h>
#include <stdbool.h>

int main (void){
    int number, number1;

    printf("Enter the first number: ");
    scanf("%d", &number);
    printf("Enter the second number: ");
    scanf("%d", &number1);
    
    int result = primesBetween(number, number1);
    printf("The number of primes between %d and %d is: %d\n", number, number1, result);
}

bool isPrime(int num) {
    if (num <= 1) {
        return 0;
    }
    for (int i = 2; i <= num / 2; ++i) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

int primesBetween(int number, int number1){
    int count = 0;
    for (int i = number + 1; i < number1; ++i) {
        if (isPrime(i)) {
            count++;
        }
        printf("%d \n", i);
    }
    return count;
}