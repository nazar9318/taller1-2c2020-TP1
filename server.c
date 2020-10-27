#define _POSIX_C_SOURCE 200112L
#include "server_usuario.h"

int main(int argc, char* argv[]) {
	user_t* user = user_create(argc, argv);
	user_run(user);
	user_destroy(user);
	return 0;
}
