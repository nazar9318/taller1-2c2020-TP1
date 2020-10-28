#include "common_vigenere.h"

void vigenere_create(vigenere_t* self, char* method, char* key, bool is) {
	self->key = key;
	self->method = method;
	self->is_crypter = is;
}

static void vigenere_code(vigenere_t* self, unsigned char* msje, size_t len) {
	size_t buff_key = 0;
	bool tipo = self->is_crypter;
	for (int i = 0; i < len; i++) {
		if ((i + buff_key) >= strlen(self->key)) {
			buff_key -= strlen(self->key);
		}
		char key_char = self->key[i + buff_key];
		unsigned char buffer = tipo ? key_char : (256 - key_char);
		msje[i] += buffer;
		if (!self->is_crypter) {
			printf("%c", msje[i]);
		}
	}
}

void vigenere_run(vigenere_t* self, unsigned char* msje, int size) {
	if (size < 0) {
		printf("Error, el mensaje a codificar es inválido\n");
	} else if (self->key == NULL) {
		printf("Error, la clave de codificacion es incorrecta\n");
	} else {
		vigenere_code(self, msje, size);
	}
}

void vigenere_destroy(vigenere_t* encoder) {
	if (encoder != NULL) {
		free(encoder);
	}
}
