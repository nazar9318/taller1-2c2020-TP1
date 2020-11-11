#include "client_usuario.h"

static int user_chooseEncoder(user_t* user) {
	char* method = selector_getMethod(&user->selector);
	char* key = selector_getKey(&user->selector);
	return encoder_create(&user->encoder, method, key, true);
}

int user_create(user_t* user, int argc, char *argv[]) {
	if (argc > 4 && argc < 7) {
		reader_create(&user->reader, stdin);
		if (socket_create(&user->cliente, argv[1], argv[2], false) == -1) {
			printf("Cliente_usuario: Fallo al crear el socket cliente\n");
			user_destroy(user);
			return -1;
		}
		if (selector_create(&user->selector, argv[3], argv[4]) == -1) {
			printf("Cliente_usuario: Fallo al crear el selector\n");
			user_destroy(user);
			return -1;
		}
		if (user_chooseEncoder(user) == -1) {
			user_destroy(user);
			return -1;
		}
		return 0;
	}
	printf("Cliente_usuario: La cantidad de argumentos insertados es inválida\n");
	return -1;
}

int user_run(user_t* user) {
	while (!reader_EOF(&user->reader)) {
		unsigned char msje[64];
		size_t len = reader_readFile(&user->reader, msje);
		if (len != -1) {
			if (encoder_run(&user->encoder, msje, len) == -1) {
				printf("Cliente_usuario: Error al encriptar mensaje\n");
				return -1;
			}
			int send = socket_send(&user->cliente, msje, len);
			if (send == -1) {
				printf("Cliente_usuario: Error al enviar mensaje\n");
				return -1;
			}
		} else {
			return -1;
		}
	}
	return 0;
}

int user_destroy(user_t* user) {
	if (socket_destroy(&user->cliente) == -1) {
		printf("Server_usuario: Error al destruir socket\n");
		return -1;
	}
	if (encoder_destroy(&user->encoder) == -1) {
		printf("Server_usuario: Error al destruir encriptador\n");
		return -1;
	}
	return 0;
}
