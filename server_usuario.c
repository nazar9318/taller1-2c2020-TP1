#include "server_usuario.h"

encoder_t* elegirTraductor(char* arg_method, char* arg_key) {
    selector_t* selector = crearSelector(arg_method, arg_key);
    char* method = NULL;
    method = devolverMetodo(selector);
    char* key = NULL;
    key = devolverClave(selector);
    encoder_t* traductor = crearEncoder(method, key, false);
    return traductor;
}

usuario_t* crearUsuario(int argc, char *argv[]) {
    usuario_t* user = malloc(sizeof(usuario_t));
    user->server = crearSocket(NULL, argv[1], true);
    user->encoder = elegirTraductor(argv[2], argv[3]);
    return user;
}

void ejecutarPrograma(usuario_t* user) {
    char* mensaje = NULL;
    size_t tamanio_mensaje = 0;
    escuchar(user->server);
    socket_t* aceptado = aceptar(user->server);
    tamanio_mensaje = recibirMensaje(aceptado, mensaje);
    printf("%s\n", codificar(user->encoder, mensaje, tamanio_mensaje));
}

void destruirUsuario(usuario_t* user) {
    destruirSocket(user->server);
    free(user);
}
