#ifndef COMMON_ENCODER_H
#define COMMON_ENCODER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common_rc4.h"
#include "common_cesar.h"
#include "common_vigenere.h"

typedef enum {CESAR, VIGENERE, RC4} crypter_mode_t;

typedef struct{
    char* key;
    char* method;
    bool is_crypter;
    void* protocol;
    crypter_mode_t mode;
}encoder_t;

//Funcion: Crea un tipo de dato encoder
//Pre condicion: Ninguna
//Post condicion: Devuelve una referencia al encoder creado.
void encoder_create(encoder_t* self, char* method, char* key, bool is);

//Funcion: Encripta o traduce el parámetro msje de tamaño size.
//Pre condicion: Encoder previamente creado.
//Post condicion: Ninguna
void encoder_run(encoder_t* self, unsigned char* msje, int size);

//Funcion: Libera la memoria reservada para el encoder
//Pre condicion: Encoder previamente creado.
//Post condicion: Memoria liberada.
void encoder_destroy(encoder_t* self);

#endif
