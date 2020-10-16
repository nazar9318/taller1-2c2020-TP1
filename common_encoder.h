#ifndef COMMON_ENCODER_H
#define COMMON_ENCODER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    char* key;
    char* method;
    bool es_encriptador;
}encoder_t;

encoder_t* crearEncoder(char* method, char* key, bool es_encriptador);

unsigned char* encript(encoder_t* encoder, unsigned char* msje, int size);

void destruirEncoder(encoder_t* encoder);

#endif

