#include "server_usuario.h"

void elegirTraductor(usuario_t* user) {
    char* method = NULL;
    method = devolverMetodo(user->selector);
    char* key = NULL;
    key = devolverClave(user->selector);
    user->encoder = crearEncoder(method, key, false);
}

usuario_t* crearUsuario(int argc, char *argv[]) {
	if (argc == 4) {
		usuario_t* user = malloc(sizeof(usuario_t));
		user->server = crearSocket(NULL, argv[1], true);
		user->selector = crearSelector(argv[2], argv[3]);
		elegirTraductor(user);
		return user;
	}
	printf("La cantidad de argumentos insertados es incorrecta.\n");
	return NULL;
}

void traducir(encoder_t* encoder, unsigned char* mensaje, size_t size) {
	unsigned char* traduccion = NULL;
	traduccion = encriptar(encoder, mensaje, size);
	if (traduccion != NULL) {
		printf("%s\n", traduccion);
	}
}

void ejecutar(usuario_t* user, socket_t* aceptado) {
	if (aceptado != NULL) {
		unsigned char* mensaje = NULL;
		int tamanio_mensaje = 0;
		tamanio_mensaje = recibirMensaje(aceptado, &mensaje);
		traducir(user->encoder, mensaje, tamanio_mensaje);
		destruirSocket(aceptado);
		free(mensaje);
	}
}

socket_t* comunicarConSocket(usuario_t* user) {
	socket_t* aceptado = NULL;
	if (escuchar(user->server) == 0) {
		aceptado = aceptar(user->server);
	}
	return aceptado;
}

void ejecutarPrograma(usuario_t* user) {
	if (user != NULL) {
		socket_t* aceptado = comunicarConSocket(user);
		ejecutar(user, aceptado);
	}
}

void destruirUsuario(usuario_t* user) {
	if (user != NULL) {
		destruirSocket(user->server);
		destruirEncoder(user->encoder);
		destruirSelector(user->selector);
		free(user);
	}
}

