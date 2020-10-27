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

//Funcion: Crea un tipo de dato encoder
//Pre condicion: Ninguna
//Post condicion: Devuelve una referencia al encoder creado.
encoder_t* encoder_create(char* method, char* key, bool es_encriptador);

//Funcion: Encripta o traduce el parámetro msje de tamaño size.
//Pre condicion: Encoder previamente creado.
//Post condicion: Ninguna
unsigned char* encoder_encode(encoder_t* self, unsigned char* msje, int size);

//Funcion: Libera la memoria reservada para el encoder
//Pre condicion: Encoder previamente creado.
//Post condicion: Memoria liberada.
void encoder_destroy(encoder_t* self);

#endif

