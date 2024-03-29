#include "server_usuario.h"

static int user_chooseTranslator(user_t* user) {
    char* method = selector_getMethod(&user->selector);
    char* key = selector_getKey(&user->selector);
    return encoder_create(&user->encoder, method, key, false);
}

int user_create(user_t* user, int argc, char *argv[]) {
	if (argc == 4) {
		if (socket_create(&user->server, NULL, argv[1], true) == -1) {
			printf("Server_usuario: Fallo al crear server\n");
			user_destroy(user);
			return -1;
		}
		if (selector_create(&user->selector, argv[2], argv[3]) == -1) {
			printf("Server_usuario: Fallo al crear el selector\n");
			user_destroy(user);
			return -1;
		}
		if (user_chooseTranslator(user) == -1) {
			user_destroy(user);
			return -1;
		}
		return 0;
	}
	printf("Server_usuario: La cantidad de argumentos es incorrecta\n");
	return -1;
}

static int user_execute(user_t* user, socket_t* aceptado) {
	if (aceptado != NULL) {
		int received = 0;
		do {
			unsigned char mensaje[64];
			received = socket_receive(aceptado, mensaje, 64);
			if (received == -1) {
				printf("Server_usuario: Error al recibir mensaje del cliente\n");
				socket_destroy(aceptado);
				return -1;
			} else {
				encoder_run(&user->encoder, mensaje, received);
			}
		} while (received > 0);
		socket_destroy(aceptado);
		printf("\n");
	}
	return 0;
}

static int user_connectClient(socket_t* aceptado, user_t* user) {
	if (socket_listen(&user->server) == 0) {
		return socket_accept(aceptado, &user->server);
	} else {
		printf("Server_usuario: Error al escuchar al cliente\n");
		return -1;
	}
}

int user_run(user_t* user) {
	socket_t aceptado;
	if (user_connectClient(&aceptado, user) == 0) {
		user_execute(user, &aceptado);
	} else {
		printf("Server_usuario: Error al conectar con el cliente\n");
		return -1;
	}
	return 0;
}

int user_destroy(user_t* user) {
	if (socket_destroy(&user->server) == -1) {
		printf("Server_usuario: Error al destruir socket\n");
		return -1;
	}
	if (encoder_destroy(&user->encoder) == -1) {
		printf("Server_usuario: Error al destruir encriptador\n");
		return -1;
	}
	return 0;
}
