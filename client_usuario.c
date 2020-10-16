#include "client_usuario.h"

void elegirEncriptador(usuario_t* user) {
	char* method = NULL;
	method = devolverMetodo(user->selector);
	char* key = NULL;
	key = devolverClave(user->selector);
	user->encoder = crearEncoder(method, key, true);
}

usuario_t* crearUsuario(int argc, char *argv[]) {
	if (argc > 4 && argc < 7) {
		usuario_t* user = malloc(sizeof(usuario_t));
		user->cliente = crearSocket(argv[1], argv[2], false);
		user->selector = crearSelector(argv[3], argv[4]);
		if (argc == 6) {
			FILE* fp = fopen(argv[5], "r");
			user->reader = crearFileReader(fp);
		} else {
			user->reader = crearFileReader(stdin);
		}
		elegirEncriptador(user);
		return user;
	} else {
		printf("La cantidad de argumentos insertados es incorrecta.\n");
		return NULL;
	}
}

void ejecutarPrograma(usuario_t* user) {
	if (user != NULL && user->cliente != NULL) {
		unsigned char* mensaje_original = NULL;
		mensaje_original = getRead(user->reader);
		size_t tamanio_mensaje = getSize(user->reader);
		unsigned char* cifrado = NULL;
		cifrado = encript(user->encoder, mensaje_original, tamanio_mensaje);
		if (cifrado != NULL) {
			enviarMensaje(user->cliente, cifrado, tamanio_mensaje);
		}
	}
}

void destruirUsuario(usuario_t* user) {
	if (user != NULL) {
		destruirSelector(user->selector);
		destruirEncoder(user->encoder);
		destruirFileReader(user->reader);
		destruirSocket(user->cliente);
		free(user);
	}
}

