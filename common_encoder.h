#ifndef COMMON_ENCODER_H
#define COMMON_ENCODER_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct{
    char* key;
    char* method;
    bool es_encriptador;
    size_t tamanio_mensaje;
}encoder_t;

encoder_t* crearEncoder(char* method, char* key, bool es_encriptador);

char* codificar(encoder_t* encoder, char* mensaje, int tamanio_mensaje);

void destruirEncoder(encoder_t* encoder);

#endif
