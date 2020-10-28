#ifndef COMMON_CESAR_H
#define COMMON_CESAR_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    char* key;
    char* method;
    bool is_crypter;
}cesar_t;

//Funcion: Crea un tipo de dato encoder
//Pre condicion: Ninguna
//Post condicion: Devuelve una referencia al encoder creado.
void cesar_create(cesar_t* self, char* method, char* key, bool is_crypter);

//Funcion: Encripta o traduce el parámetro msje de tamaño size.
//Pre condicion: Encoder previamente creado.
//Post condicion: Ninguna
void cesar_run(cesar_t* self, unsigned char* msje, int size);

#endif
