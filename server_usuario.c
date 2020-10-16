#include "server_usuario.h"

void elegirTraductor(usuario_t* user) {
    char* method = NULL;
    method = devolverMetodo(user->selector);
    char* key = NULL;
    key = devolverClave(user->selector);
    user->encoder = crearEncoder(method, key, false);
}

usuario_t* crearUsuario(int argc, char *argv[]) {
    usuario_t* user = malloc(sizeof(usuario_t));
    user->server = crearSocket(NULL, argv[1], true);
    user->selector = crearSelector(argv[2], argv[3]);
    elegirTraductor(user);
    return user;
}

void ejecutarPrograma(usuario_t* user) {
    unsigned char* mensaje = NULL;
    socket_t* aceptado = NULL;
    if (escuchar(user->server) == 0) {
	aceptado = aceptar(user->server);
	if ((aceptado) != NULL) {
        int tamanio_mensaje = 0;
		tamanio_mensaje = recibirMensaje(aceptado, &mensaje);
		printf("%s\n", encript(user->encoder, mensaje, tamanio_mensaje));
		destruirSocket(aceptado);
	}
    }
    free(mensaje);
}

void destruirUsuario(usuario_t* user) {
    destruirSocket(user->server);
    destruirEncoder(user->encoder);
    destruirSelector(user->selector);
    free(user);
}

