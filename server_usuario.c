#include "server_usuario.h"

static void user_chooseTranslator(user_t* user) {
    char* method = NULL;
    method = selector_getMethod(&user->selector);
    char* key = NULL;
    key = selector_getKey(&user->selector);
    encoder_create(&user->encoder, method, key, false);
}

user_t* user_create(int argc, char *argv[]) {
	if (argc == 4) {
		user_t* user = malloc(sizeof(user_t));
		if (user == NULL) {
			printf("Fallo al alocar memoria para el user\n");
			return NULL;
		}
		socket_create(&user->server, NULL, argv[1], true);
		if (&user->server == NULL) {
			printf("Fallo al crear server\n");
			user_destroy(user);
			return NULL;
		}
		selector_create(&user->selector, argv[2], argv[3]);
		user_chooseTranslator(user);
		return user;
	}
	printf("La cantidad de argumentos insertados es incorrecta.\n");
	return NULL;
}

static void user_translate(user_t* self, unsigned char* msje, size_t len) {
	if (len > 0) {
		encoder_run(&self->encoder, msje, len);
	}
}

static void user_execute(user_t* user, socket_t* aceptado) {
	if (aceptado != NULL) {
		unsigned char mensaje[64];
		int received = 0;
		do {
			received = socket_receive(aceptado, mensaje, 64);
			if (received == -1) {
				printf("Error al recibir mensaje del cliente\n");
			} else {
				user_translate(user, mensaje, received);
			}
		} while (received > 0);
		socket_destroy(aceptado);
		printf("\n");
	}
}

static void user_connectClient(socket_t* aceptado, user_t* user) {
	if (socket_listen(&user->server) == 0) {
		socket_accept(aceptado, &user->server);
	} else {
		printf("Error al escuchar al cliente\n");
	}
}

void user_run(user_t* user) {
	if (user != NULL) {
		socket_t aceptado;
		user_connectClient(&aceptado, user);
		user_execute(user, &aceptado);
	}
}

void user_destroy(user_t* user) {
	if (user != NULL) {
		socket_destroy(&user->server);
		encoder_destroy(&user->encoder);
		selector_destroy(&user->selector);
		free(user);
	}
}
