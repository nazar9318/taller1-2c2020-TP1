#include "common_cesar.h"

void cesar_create(cesar_t* self, char* method, char* key, bool is_crypter) {
	self->key = key;
	self->method = method;
	self->is_crypter = is_crypter;
}

static void cesar_code(cesar_t* self, unsigned char* msje, size_t len) {
	bool is_crypter = self->is_crypter;
	unsigned int u_key = (unsigned int) strtol(self->key, (char**) NULL,10);
	if (u_key == 0 && self->key[0] != '0') {
		//error
	}
	for (int i = 0; i < len; i++) {
		msje[i] += is_crypter ? u_key : 256 - u_key;
		if (!self->is_crypter) {
			printf("%c", msje[i]);
		}
	}
}

void cesar_run(cesar_t* self, unsigned char* msje, int size) {
	if (size < 0) {
		printf("Error, el mensaje a codificar es inválido\n");
	} else if (self->key == NULL) {
		printf("Error, la clave de codificacion es incorrecta\n");
	} else {
		cesar_code(self, msje, size);
	}
}

void cesar_destroy(cesar_t* self) {}
