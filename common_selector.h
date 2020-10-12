#ifndef COMMON_SELECTOR_H
#define COMMON_SELECTOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char* key;
    char* method;
}selector_t;

selector_t* crearSelector(char* argv_method, char* argv_key);

char* devolverMetodo(selector_t* selector);

char* devolverClave(selector_t* selector);

void destruirSelector(selector_t* selector);

#endif 
