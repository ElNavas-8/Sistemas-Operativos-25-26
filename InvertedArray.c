#include <stdio.h>
void invertir(int myNumbers[], int inNumbers[], int i, int size);

int main (void)
{
    int myNumbers[4]= {323, 32, 255, 795};
    int size = sizeof(myNumbers) / sizeof(myNumbers[0]);
    int inNumbers[4]={0};

    invertir(myNumbers, inNumbers, 0, size);
    for (int i = 0; i != size; ++i)
        printf("%d ", inNumbers[i]);
    putchar('\n');
    return 0;
}

void invertir(int myNumbers[], int inNumbers[],int i, int size){
  if (((size-1)-i)==0) {
    inNumbers[i]=myNumbers[0];
  }
  else {
    inNumbers[i]=myNumbers[(size-1)-i];
    invertir(myNumbers, inNumbers,++i, size); 
  }
}