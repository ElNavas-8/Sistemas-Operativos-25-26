#include <stdio.h>
void invertir(int myNumbers[], int size);

int main (void)
{
    int myNumbers[4]= {323, 32, 255, 795};
    int size = sizeof(myNumbers) / sizeof(myNumbers[0]);

    invertir(myNumbers, size);
    for (int i = 0; i != size; ++i)
        printf("%d ", myNumbers[i]);
    puts("\n");
    return 0;
}

void invertir(int *myNumbers, int size){
  int *fin = myNumbers + (size-1);
  int aux;
  
  while (myNumbers < fin) {
    aux = *myNumbers;
    *myNumbers = *fin;
    *fin = aux;
    
    myNumbers++;
    fin--;
  }
}