#include "client_usuario.h"

encoder_t* elegirEncriptador(usuario_t* user) {
    char* method = NULL;
    method = devolverMetodo(user->selector);
    char* key = NULL;
    key = devolverClave(user->selector);
    encoder_t* encriptador = crearEncoder(method, key, true);
    return encriptador;
}

usuario_t* crearUsuario(int argc, char *argv[]) {
    usuario_t* user = malloc(sizeof(usuario_t));
    user->cliente = crearSocket(argv[1], argv[2], false);
    user->selector = crearSelector(argv[3], argv[4]);
    user->reader = crearFileReader(stdin);
    user->encoder = elegirEncriptador(user);
    return user;
}

void ejecutarPrograma(usuario_t* user) {
	char* mensaje_original = NULL;
	mensaje_original = getRead(user->reader);
	size_t tamanio_mensaje = getSize(user->reader);
	char* cifrado = NULL;
	cifrado = codificar(user->encoder, mensaje_original, tamanio_mensaje);
	enviarMensaje(user->cliente, cifrado, tamanio_mensaje);
}

void destruirUsuario(usuario_t* user) {
    destruirSelector(user->selector);
    destruirEncoder(user->encoder);
    destruirFileReader(user->reader);
    destruirSocket(user->cliente);
    free(user);
}
