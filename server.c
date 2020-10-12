#define _POSIX_C_SOURCE 200112L
#include "server_usuario.h"

int main(int argc, char* argv[]) {
	usuario_t* user = crearUsuario(argc, argv);
	ejecutarPrograma(user);
	destruirUsuario(user);
	return 0;
}
