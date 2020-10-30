#include "common_vigenere.h"
#include <errno.h>

vigenere_t* vigenere_create(char* key, bool is) {
	vigenere_t* self = malloc(sizeof(vigenere_t));
	if (self != NULL) {
		self->key = key;
		self->is_crypter = is;
		self->pos = 0;
	} else {
		printf("Vigenere: Fallo al alocar memoria%s\n", strerror(errno));
	}
	return self;
}

static void vigenere_code(vigenere_t* self, unsigned char* msje, size_t len) {
	bool tipo = self->is_crypter;
	for (int i = 0; i < len; i++) {
		if (self->pos == strlen(self->key)) {
			self->pos = 0;
		}
		char key_char = self->key[self->pos];
		unsigned char buffer = tipo ? key_char : (256 - key_char);
		msje[i] += buffer;
		if (!self->is_crypter) {
			printf("%c", msje[i]);
		}
		self->pos++;
	}
}

void vigenere_run(vigenere_t* self, unsigned char* msje, int size) {
	if (size < 0) {
		printf("Vigenere: Error, el mensaje a codificar es inválido\n");
	} else if (self->key == NULL) {
		printf("Vigenere: Error, la clave de codificacion es incorrecta\n");
	} else {
		vigenere_code(self, msje, size);
	}
}
