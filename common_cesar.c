#include "common_cesar.h"
#include <errno.h>
#include <ctype.h>

cesar_t* cesar_create(char* key, bool is_crypter) {
	cesar_t* self = malloc(sizeof(cesar_t));
	if (self != NULL) {
		for (int i = 0; key[i] != '\0'; i++) {
			if (isdigit(key[i]) == 0) {
				printf("Cesar: La clave de encriptación debe ser numérica\n");
				free(self);
				return NULL;
			}
		}
		self->key = (unsigned int) strtol(key, (char**)NULL,10);
		if (errno == EINVAL) {
			printf("Fallo al leer la clave %s\n", strerror(errno));	
			free(self);
		}
		self->is_crypter = is_crypter;
	} else {
		printf("Cesar: Fallo al alocar memoria%s\n", strerror(errno));
	}
	return self;
}

static void cesar_code(cesar_t* self, unsigned char* msje, size_t len) {
	bool is_crypter = self->is_crypter;
	for (int i = 0; i < len; i++) {
		msje[i] += is_crypter ? self->key : 256 - self->key;
		if (!self->is_crypter) {
			printf("%c", msje[i]);
		}
	}
}

void cesar_run(cesar_t* self, unsigned char* msje, int size) {
	if (size < 0) {
		printf("Cesar: Error, el mensaje a codificar es inválido\n");
	} else {
		cesar_code(self, msje, size);
	}
}

void cesar_destroy(cesar_t* self) {}
