#ifndef SERVER_USUARIO_H
#define SERVER_USUARIO_H
#include "common_socket.h"
#include "common_selector.h"
#include "common_encoder.h"
#include <stdio.h>

typedef struct{
    socket_t server;
    encoder_t encoder;
    selector_t selector;
}user_t;

//Pre condicion: Ninguna
//Post condicion: Devuelve una referencia al cliente_usuario creado
//o NULL en caso de algún error al alocar memoria o al crear los atributos.
int user_create(user_t* user, int argc, char *argv[]);

//Funcion: Ejecuta el flujo del programa completo
//Pre condicion: User previamente creado.
//Post condicion: Devuelve -1 en caso de error, o 0 si no hubo errores.
int user_run(user_t* user);

//Funcion: Libera la memoria reservada.
//Pre condicion: User previamente creado
//Post condicion: Devuelve -1 en caso de error, o 0 si no hubo errores.
int user_destroy(user_t* user);

#endif
