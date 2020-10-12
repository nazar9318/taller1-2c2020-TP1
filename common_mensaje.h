#ifndef COMMON_MENSAJE_H
#define COMMON_MENSAJE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char* contenido;
}mensaje_t;

mensaje_t* crearMensaje(char* mensaje);

size_t devolverTamanio(mensaje_t* mensaje);

char* devolverMensaje(mensaje_t* mensaje);

void destruirMensaje(mensaje_t* mensaje);

#endif
