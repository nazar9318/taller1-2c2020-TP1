#ifndef CLIENT_USUARIO_H
#define CLIENT_USUARIO_H
#include "common_socket.h"
#include "common_encoder.h"
#include "common_selector.h"
#include "common_file_reader.h"

typedef struct{
    socket_t* cliente;
    encoder_t* encoder;
    selector_t* selector;
    file_reader_t* reader;
}usuario_t;

usuario_t* crearUsuario(int argc, char *argv[]);

void ejecutarPrograma(usuario_t* user);

void destruirUsuario(usuario_t* user);

#endif
