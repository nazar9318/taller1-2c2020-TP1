#ifndef COMMON_VIGENERE_H
#define COMMON_VIGENERE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    char* key;
    char* method;
    bool is_crypter;
}vigenere_t;

//Funcion: Crea un tipo de dato encoder
//Pre condicion: Ninguna
//Post condicion: Devuelve una referencia al encoder creado.
void vigenere_create(vigenere_t* self, char* method, char* key, bool is);

//Funcion: Encripta o traduce el parámetro msje de tamaño size.
//Pre condicion: Encoder previamente creado.
//Post condicion: Ninguna
void vigenere_run(vigenere_t* self, unsigned char* msje, int size);

//Funcion: Libera la memoria reservada para el encoder
//Pre condicion: Encoder previamente creado.
//Post condicion: Memoria liberada.
void vigenere_destroy(vigenere_t* self);

#endif
