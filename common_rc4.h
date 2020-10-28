#ifndef COMMON_RC4_H
#define COMMON_RC4_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    char* key;
    bool is_crypter;
    unsigned int i;
    unsigned int j;
    unsigned char s_box[256];
}rc4_t;

//Funcion: Crea un tipo de dato encoder
//Pre condicion: Ninguna
//Post condicion: Devuelve una referencia al encoder creado.
rc4_t* rc4_create(char* key, bool is_crypter);

//Funcion: Encripta o traduce el parámetro msje de tamaño size.
//Pre condicion: Encoder previamente creado.
//Post condicion: Ninguna
void rc4_run(rc4_t* self, unsigned char* msje, int size);

#endif
