#define _POSIX_C_SOURCE 200112L
#include "server_usuario.h"

int main(int argc, char* argv[]) {
	user_t user;
	if (user_create(&user, argc, argv) == -1) {
		printf("No se pudo crear al usuario\n");
		return 0;
	}
	if (user_run(&user) == -1) {
		printf("Error al ejecutar usuario\n");
		return 0;
	}
	if (user_destroy(&user) == -1) {
		printf("Error al destruir usuario\n");
	}
	return 0;
}
