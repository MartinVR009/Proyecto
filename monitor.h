#ifndef __MONITOR_H__
#define __MONITOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct {
    int TAM;
    char buffer[TAM];
    int tipo_sensor;
} Buffer;

Buffer* crear_buffer(int TAM) {
    Buffer *nuevo_buffer = malloc(sizeof(Buffer));
    if (nuevo_buffer != NULL) {
        nuevo_buffer->TAM = TAM;
        nuevo_buffer->buffer = malloc(TAM * sizeof(char));
        if (nuevo_buffer->buffer == NULL) {
            free(nuevo_buffer);
            return NULL; // Error al asignar memoria para el buffer
        }
    }
    return nuevo_buffer;
}

void liberar_buffer(Buffer *buffer) {
    if (buffer != NULL) {
        free(buffer->buffer);
        free(buffer);
    }
}

Buffer buffer_temp, buffer_ph;
sem_t sem_buffer_temp, sem_buffer_ph;

void* recolector(void* arg);
void* ph(void* arg);
void* temperatura(void* arg);

#include "monitor.c"

#endif
