#include "server_usuario.h"

static void elegirTraductor(user_t* user) {
    char* method = NULL;
    method = selector_getMethod(user->selector);
    char* key = NULL;
    key = selector_getKey(user->selector);
    user->encoder = encoder_create(method, key, false);
}

user_t* user_create(int argc, char *argv[]) {
	if (argc == 4) {
		user_t* user = malloc(sizeof(user_t));
		user->server = crearSocket(NULL, argv[1], true);
		user->selector = selector_create(argv[2], argv[3]);
		elegirTraductor(user);
		return user;
	}
	printf("La cantidad de argumentos insertados es incorrecta.\n");
	return NULL;
}

static void traducir(encoder_t* encoder, unsigned char* mensaje, size_t size) {
	unsigned char* traduccion = NULL;
	traduccion = encoder_encode(encoder, mensaje, size);
	if (traduccion != NULL) {
		printf("%s\n", traduccion);
	}
}

static void ejecutar(user_t* user, socket_t* aceptado) {
	if (aceptado != NULL) {
		unsigned char* mensaje = NULL;
		int tamanio_mensaje = 0;
		tamanio_mensaje = recibirMensaje(aceptado, &mensaje);
		traducir(user->encoder, mensaje, tamanio_mensaje);
		destruirSocket(aceptado);
		free(mensaje);
	}
}

static socket_t* comunicarConSocket(user_t* user) {
	socket_t* aceptado = NULL;
	if (escuchar(user->server) == 0) {
		aceptado = aceptar(user->server);
	}
	return aceptado;
}

void user_run(user_t* user) {
	if (user != NULL) {
		socket_t* aceptado = comunicarConSocket(user);
		ejecutar(user, aceptado);
	}
}

void user_destroy(user_t* user) {
	if (user != NULL) {
		destruirSocket(user->server);
		encoder_destroy(user->encoder);
		selector_destroy(user->selector);
		free(user);
	}
}
