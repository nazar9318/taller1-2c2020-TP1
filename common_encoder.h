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
encoder_t* crearEncoder(char* method, char* key, bool es_encriptador);

//Funcion: Encripta o traduce el parámetro msje de tamaño size.
//Pre condicion: Encoder previamente creado.
//Post condicion: Ninguna
unsigned char* encript(encoder_t* encoder, unsigned char* msje, int size);

//Funcion: Libera la memoria reservada para el encoder
//Pre condicion: Encoder previamente creado.
//Post condicion: Memoria liberada.
void destruirEncoder(encoder_t* encoder);

#endif

