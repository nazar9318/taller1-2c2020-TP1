#ifndef SERVER_USUARIO_H
#define SERVER_USUARIO_H
#include "common_socket.h"
#include "common_selector.h"
#include "common_encoder.h"
#include <stdio.h>

typedef struct{
    socket_t* server;
    encoder_t* encoder;
}usuario_t;

usuario_t* crearUsuario(int argc, char *argv[]);

void ejecutarPrograma(usuario_t* user);

void destruirUsuario(usuario_t* user);

#endif
