#include "monitor.h"

void* recolector(void *arg)
{

    // Declaración de variables para almacenar los parámetros
    int tam_buffer = 0;
    char* file_temp = NULL;
    char* file_ph = NULL;
    char* pipe_nominal = NULL;

    // Verificación de la cantidad de argumentos
    if (argc != 9) {
        printf("Uso: %s -b tam_buffer -t file_temp -h file_ph -p pipe_nominal\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Procesamiento de los argumentos
    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-b") == 0) {
            tam_buffer = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-t") == 0) {
            file_temp = argv[i + 1];
        } else if (strcmp(argv[i], "-h") == 0) {
            file_ph = argv[i + 1];
        } else if (strcmp(argv[i], "-p") == 0) {
            pipe_nominal = argv[i + 1];
        } else {
            printf("Argumento desconocido: %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    // Verificar que los parámetros obligatorios no estén vacíos
    if (tam_buffer == 0 || file_temp == NULL || file_ph == NULL || pipe_nominal == NULL) {
        printf("Faltan parámetros obligatorios.\n");
        exit(EXIT_FAILURE);
    }

    Buffer *mi_buffer = crear_buffer(tam_buffer);
    if (mi_buffer == NULL) {
        printf("Error al crear el buffer.\n");
        exit(EXIT_FAILURE);
    }

    char* pipe_nominal = (char*)arg;
    int pipe_fd;
    char buffer[TAM];

    // Se abre el pipe nominal

    pipe_fd = open(pipe_nominal, O_RDONLY);

    if (pipe_fd == -1) {
        printf("Error al abrir el pipe\n");
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Se leen las medidas de los sensores

    while (read(pipe_fd, buffer, TAM) > 0) {
        int tipo_sensor;
        char medida[TAM];

        // Se extrae tipo de sensor y medida del mensaje recibido

        sscanf(buffer, "%d %s", &tipo_sensor, medida);

        // Se coloca la medida en el buffer correspondiente

        if (tipo_sensor == 1) { // Temperatura

            sem_wait(&sem_buffer_temp); // Se bloquea el hilo hasta que el semáforo sem_buffer_temp esté disponible
            strncpy(buffer_temp.buffer, medida, TAM); // Se ccopia la medida recibida del sensor en el buffer de medidas de temperatura
            buffer_temp.tipo_sensor = tipo_sensor; // Se asigna el tipo de sensor (1 para temperatura)
            sem_post(&sem_buffer_temp); // Se incrementa el valor del semáforo para que sea usado por otro hilo

        } else if (tipo_sensor == 2) { // PH

            sem_wait(&sem_buffer_ph);
            strncpy(buffer_ph.buffer, medida, TAM);
            buffer_ph.tipo_sensor = tipo_sensor;
            sem_post(&sem_buffer_ph);

        } else {
            printf("Error: Medida recibida con tipo de sensor inválido.\n");
        }
    }

    // Cerrar el pipe

    close(pipe_fd);
    liberar_buffer(mi_buffer);
    return NULL;
}

void* ph(void* arg) {

}

void* temperatura(void* arg) {

}
