#include <stdio.h>

/*Programa que genera las 10 primeras tablas de multiplicar
 * Para ello hacemos uso de 2 bucles for anidados. El primero cuenta las 10 tablas
 * que tenemos que generar, el segundo los 10 elementos que compone cada tabla*/
 
 
int main (void)
{
	int i, j;
	for (i=1;i<=10;i++)
	{
		printf("\nTabla del %d\n", i);
		for (j=1;j<=10;j++)
		{
			printf("%d x %d = %d\n", i, j, i*j);
		}
	}
	return 0;
}
