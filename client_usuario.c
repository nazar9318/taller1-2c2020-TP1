#include "client_usuario.h"

static void user_chooseEncoder(user_t* user) {
	char* method = NULL;
	method = selector_getMethod(&user->selector);
	char* key = NULL;
	key = selector_getKey(&user->selector);
	encoder_create(&user->encoder, method, key, true);
}

user_t* user_create(int argc, char *argv[]) {
	if (argc > 4 && argc < 7) {
		user_t* user = malloc(sizeof(user_t));
		if (user == NULL) {
			printf("Fallo al alocar memoria para el usuario\n");
			return NULL;
		}
		reader_create(&user->reader, stdin);
		socket_create(&user->cliente, argv[1], argv[2], false);
		if (&user->cliente == NULL) {
			printf("Fallo al crear el socket cliente\n");
			user_destroy(user);
			return NULL;
		}
		selector_create(&user->selector, argv[3], argv[4]);
		user_chooseEncoder(user);
		return user;
	}
	printf("La cantidad de argumentos insertados es incorrecta.\n");
	return NULL;
}

void user_run(user_t* user) {
	if (user != NULL && &user->cliente != NULL) {
		int send = 0;
		while (!reader_EOF(&user->reader)) {
			unsigned char msje[64];
			reader_readFile(&user->reader, msje);
			encoder_run(&user->encoder, msje, 64);
			send = socket_send(&user->cliente, msje, reader_getRead(&user->reader));
			if (send == -1) {
				printf("Error al enviar mensaje\n");
				break;
			}
		}
	}
}

void user_destroy(user_t* user) {
	if (user != NULL) {
		selector_destroy(&user->selector);
		encoder_destroy(&user->encoder);
		reader_destroy(&user->reader);
		socket_destroy(&user->cliente);
		free(user);
	}
}
