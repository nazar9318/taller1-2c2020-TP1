#define _POSIX_C_SOURCE 200112L
#include "server_usuario.h"

int main(int argc, char* argv[]) {
	user_t* user = user_create(argc, argv);
	if (user == NULL) {
		printf("No se pudo crear al usuario\n");
		return 0;
	}
	user_run(user);
	if (user_destroy(user) == -1) {
		printf("Error al destruir usuario\n");
	}
	return 0;
}
