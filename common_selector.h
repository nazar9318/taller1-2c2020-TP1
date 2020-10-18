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
//Post condicion: Devuelve una referencia al selector creado.
selector_t* crearSelector(char* argv_method, char* argv_key);

//Funcion: Devuelve el método del selector.
//Pre condicion: Selector previamente creado.
//Post condicion: Devuelve un puntero al método.
char* devolverMetodo(selector_t* selector);

//Funcion: Devuelve la clave del selector.
//Pre condicion: Selector previamente creado.
//Post condicion: Devuelve un puntero a la clave del método.
char* devolverClave(selector_t* selector);

//Funcion: Libera la memoria reservada para el selector.
//Pre condicion: Selector previamente creado.
//Post condicion: Memoria liberada.
void destruirSelector(selector_t* selector);

#endif 
