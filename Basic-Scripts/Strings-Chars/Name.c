
int main() {
    char nombre[50], edad[3];
    int bytesLeidos;

    char mensajeNombre[] = "¿Cuál es tu nombre? ";
    write(1, mensajeNombre, sizeof(mensajeNombre)-1);
    bytesLeidos = read(0, nombre, sizeof(nombre));
    if (bytesLeidos > 0) {
        nombre[bytesLeidos] = '\0';
    }

    char mensajeEdad[] = "¿Cuál es tu edad? ";
    write(1, mensajeEdad, sizeof(mensajeEdad)-1);
    bytesLeidos = read(0, edad, sizeof(edad));
    if (bytesLeidos > 0) {
        edad[bytesLeidos] = '\0';
    }

    write (1, "Hola ", 5);
    int lenNombre = 0;
    while (nombre[lenNombre] != '\0') lenNombre++;
    write(1, nombre, lenNombre);

    write(1, ", tienes ", 9);
    int lenEdad = 0;
    while (edad[lenEdad] != '\0') lenEdad++;
    write(1, edad, lenEdad);
    
    write(1, " años.\n", 7);

    return 0;
}
