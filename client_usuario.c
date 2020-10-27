#include "client_usuario.h"

static void user_chooseEncoder(user_t* user) {
	char* method = NULL;
	method = selector_getMethod(user->selector);
	char* key = NULL;
	key = selector_getKey(user->selector);
	user->encoder = encoder_create(method, key, true);
}

user_t* user_create(int argc, char *argv[]) {
	if (argc > 4 && argc < 7) {
		user_t* user = malloc(sizeof(user_t));
		user->reader = reader_create(stdin);
		user->cliente = crearSocket(argv[1], argv[2], false);
		user->selector = selector_create(argv[3], argv[4]);
		user_chooseEncoder(user);
		return user;
	}
	printf("La cantidad de argumentos insertados es incorrecta.\n");
	return NULL;
}

void user_run(user_t* user) {
	if (user != NULL && user->cliente != NULL) {
		unsigned char* mensaje_original = NULL;
		mensaje_original = reader_getRead(user->reader);
		size_t tamanio = reader_getSize(user->reader);
		unsigned char* cifrado = NULL;
		cifrado = encoder_encode(user->encoder, mensaje_original, tamanio);
		if (cifrado != NULL) {
			enviarMensaje(user->cliente, cifrado, tamanio);
		}
	}
}

void user_destroy(user_t* user) {
	if (user != NULL) {
		selector_destroy(user->selector);
		encoder_destroy(user->encoder);
		reader_destroy(user->reader);
		destruirSocket(user->cliente);
		free(user);
	}
}

