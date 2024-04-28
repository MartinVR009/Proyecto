#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "monitor.h"

int main(int argc, char* argv[]) {

    int tipo_sensor = 0;
    int tiempo = 0;
    char* archivo = "";
    char* pipe_nominal = "";

    // Verificación de la cantidad de argumentos
    if (argc != 9) {
        printf("Para llamar a la funcion se debe hacer de modo: %s -s tipo_sensor -t tiempo -f archivo -p pipe_nominal\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Procesamiento de los argumentos
    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-s") == 0) {
            tipo_sensor = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-t") == 0) {
            tiempo = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-f") == 0) {
            archivo = argv[i + 1];
        } else if (strcmp(argv[i], "-p") == 0) {
            pipe_nominal = argv[i + 1];
        } else {
            printf("Argumento desconocido: %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    if (tipo_sensor == 0 || tiempo == 0 || archivo == NULL || pipe_nominal == NULL) {
        printf("Faltan parámetros obligatorios.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
