#include "client_usuario.h"

void elegirEncriptador(usuario_t* user) {
	char* method = NULL;
	method = devolverMetodo(user->selector);
	char* key = NULL;
	key = devolverClave(user->selector);
	user->encoder = crearEncoder(method, key, true);
}

void abrirArchivo(usuario_t* user, int argc, char* argv[]) {
	if (argc == 6) {
		FILE* fp = fopen(argv[5], "r");
		user->reader = crearFileReader(fp);
	} else {
		user->reader = crearFileReader(stdin);
	}
}

usuario_t* crearUsuario(int argc, char *argv[]) {
	if (argc > 4 && argc < 7) {
		usuario_t* user = malloc(sizeof(usuario_t));
		user->cliente = crearSocket(argv[1], argv[2], false);
		user->selector = crearSelector(argv[3], argv[4]);
		abrirArchivo(user, argc, argv);
		elegirEncriptador(user);
		return user;
	}
	printf("La cantidad de argumentos insertados es incorrecta.\n");
	return NULL;
}

void ejecutarPrograma(usuario_t* user) {
	if (user != NULL && user->cliente != NULL) {
		unsigned char* mensaje_original = NULL;
		mensaje_original = getRead(user->reader);
		size_t tamanio = getSize(user->reader);
		unsigned char* cifrado = NULL;
		cifrado = encriptar(user->encoder, mensaje_original, tamanio);
		if (cifrado != NULL) {
			enviarMensaje(user->cliente, cifrado, tamanio);
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

