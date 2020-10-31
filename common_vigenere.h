#ifndef COMMON_VIGENERE_H
#define COMMON_VIGENERE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    char* key;
    bool is_crypter;
    int pos;
}vigenere_t;

//Funcion: Crea un tipo de dato encoder_vigenere
//Pre condicion: Ninguna
//Post condicion: Devuelve una referencia al encoder creado.
vigenere_t* vigenere_create(char* key, bool is);

//Funcion: Encripta o traduce el parámetro msje de tamaño size.
//Pre condicion: Encoder previamente creado.
//Post condicion: Ninguna
void vigenere_run(vigenere_t* self, unsigned char* msje, int size);

#endif
