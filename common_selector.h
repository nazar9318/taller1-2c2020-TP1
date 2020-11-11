#ifndef COMMON_SELECTOR_H
#define COMMON_SELECTOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char* key;
    char* method;
}selector_t;

//Funcion: Crea un tipo de dato selector.
//Pre condicion: Ninguna.
//Post condicion: Devuelve 0 si no hubo error, -1 si lo hubo
int selector_create(selector_t* self, char* argv_method, char* argv_key);

//Funcion: Devuelve el método del selector.
//Pre condicion: Selector previamente creado.
//Post condicion: Devuelve un puntero al método.
char* selector_getMethod(selector_t* self);

//Funcion: Devuelve la clave del selector.
//Pre condicion: Selector previamente creado.
//Post condicion: Devuelve un puntero a la clave del método.
char* selector_getKey(selector_t* self);

void selector_destroy(selector_t* self);

#endif 
