#include <stdio.h>

void printArray(int arr[], int size);

int main() {
    int size;

    printf("¿De qué tamaño quieres el array?: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Error: El tamaño debe ser mayor a 0.\n");
        return 1;
    }

    int array[size]; 

    printf("\n--- Rellenando el array ---\n");
    for (int i = 0; i < size; i++) {
        printf("Introduce el valor para la posición [%d]: ", i);
        scanf("%d", &array[i]);
    }

    printf("\nEstado actual del array:\n");
    printArray(array, size);

    int index, newValue;
    printf("\n¿Quieres modificar alguna posición? (0 a %d): ", size - 1);
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        printf("Nuevo valor para [%d]: ", index);
        scanf("%d", &newValue);
        array[index] = newValue; 

        printf("\nArray final actualizado:\n");
        printArray(array, size);
    } else {
        printf("Índice no válido, no se hicieron cambios.\n");
    }

    return 0;
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}