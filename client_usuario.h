#ifndef CLIENT_USUARIO_H
#define CLIENT_USUARIO_H
#include "common_socket.h"
#include "common_encoder.h"
#include "common_selector.h"
#include "common_file_reader.h"

typedef struct{
    socket_t cliente;
    encoder_t encoder;
    selector_t selector;
    reader_t reader;
}user_t;

//Funcion: Crea un tipo de dato cliente usuario
//Pre condicion: Ninguna
//Post condicion: Devuelve -1 en caso de error, o 0 si no hubo errores.
int user_create(user_t* user, int argc, char *argv[]);

//Funcion: Ejecuta el flujo del programa completo
//Pre condicion: User previamente creado.
//Post condicion: Devuelve -1 en caso de error, o 0 si no hubo errores.
int user_run(user_t* user);

//Funcion: Libera la memoria reservada para los atributos del usuario
//Pre condicion: User previamente creado
//Post condicion: Devuelve -1 en caso de error, o 0 si no hubo errores.
int user_destroy(user_t* user);

#endif
