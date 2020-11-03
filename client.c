#define _POSIX_C_SOURCE 200112L
#include "client_usuario.h"

int main(int argc, char *argv[]) {
	user_t user;
	if (user_create(&user, argc, argv) == -1) {
		printf("No se pudo crear al usuario\n");
		return 0;
	}
	if (user_run(&user) == -1) {
		printf("Error al ejecutar el usuario\n");
	}
	if (user_destroy(&user) == -1) {
		printf("Error al destrui el usuario\n");
	}
	return 0;
}
