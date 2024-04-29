#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "monitor.h"


struct Sensor{
    int tipo_sensor; 
    int tiempo;
    char* archivo; 
    char* pipe_nominal;
};

void imprimirDatos(struct Sensor sensor);


int main(int argc, char* argv[]) {

    
    struct Sensor miSensor;

    miSensor.tipo_sensor = -1;
    miSensor.tiempo = -1;
    miSensor.archivo = NULL;
    miSensor.pipe_nominal = NULL;
    

    // Verificación de la cantidad de argumentos
    if (argc != 9) {
        printf("Para llamar a la funcion se debe hacer de modo: %s -s tipo_sensor -t tiempo -f archivo -p pipe_nominal\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Procesamiento de los argumentos
    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-s") == 0) {
            miSensor.tipo_sensor = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-t") == 0) {
            miSensor.tiempo = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-f") == 0) {
            miSensor.archivo = argv[i + 1];
        } else if (strcmp(argv[i], "-p") == 0) {
            miSensor.pipe_nominal = argv[i + 1];
        } else {
            printf("Argumento desconocido: %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    if (miSensor.tipo_sensor == 0 || miSensor.archivo == 0 || archivo == NULL || pipe_nominal == NULL) {
        printf("Faltan parámetros obligatorios.\n");
        exit(EXIT_FAILURE);
    }

    

    return 0;
}

void imprimirDatos(struct Sensor sensor){
  printf("Tipo: %d\n", sensor.tipo_sensor);
  printf("Tiempo: %d\n", sensor.tiempo);
  printf("Nombre del archivo: %s\n", sensor.archivo);
  printf("Nombre del pipe: %s\n", sensor.pipe_nominal);
}

