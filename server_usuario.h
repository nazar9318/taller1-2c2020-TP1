#ifndef SERVER_USUARIO_H
#define SERVER_USUARIO_H
#include "common_socket.h"
#include "common_selector.h"
#include "common_encoder.h"
#include <stdio.h>

typedef struct{
    socket_t* server;
    encoder_t* encoder;
    selector_t* selector;
}user_t;

//Funcion: Crea un tipo de dato cliente usuario
//Pre condicion: Ninguna
//Post condicion: Devuelve una referencia al cliente_usuario creado.
user_t* user_create(int argc, char *argv[]);

//Funcion: Ejecuta el flujo del programa completo
//Pre condicion: User previamente creado.
//Post condicion: Ninguna
void user_run(user_t* user);

//Funcion: Libera la memoria reservada.
//Pre condicion: User previamente creado
//Post condicion: Memoria liberada
void user_destroy(user_t* user);

#endif
