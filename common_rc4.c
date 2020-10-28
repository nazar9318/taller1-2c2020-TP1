#include "common_rc4.h"

static void rc4_swap(unsigned char* s, unsigned int a, unsigned int b) {
	unsigned char aux;
	aux = s[a];
	s[a] = s[b];
	s[a] = aux;
}

static void rc4_initializeSBOX(rc4_t* self) {
	for (unsigned int i = 0; i < 256; i++) {
		self->s_box[i] = i;
	}
	unsigned int j = 0;
	for (unsigned int i = 0; i < 256; i++) {
		j = (j + self->s_box[i] + self->key[i % strlen(self->key)]) & 255;
		rc4_swap(self->s_box, i, j);
	}
}

rc4_t* rc4_create(char* key, bool is_crypter) {
	rc4_t* self = malloc(sizeof(rc4_t));
	self->key = key;
	self->is_crypter = is_crypter;
	self->i = 0;
    self->j = 0;
	rc4_initializeSBOX(self);
	return self;
}

static void rc4_code(rc4_t* self, unsigned char* msje, size_t size) {
	for (int k = 0; k < size; k++) {
		self->i = (self->i + 1) & 255;
		self->j = (self->j + self->s_box[self->i]) & 255;
		rc4_swap(self->s_box, self->i, self->j);
		unsigned int t = (self->s_box[self->i] + self->s_box[self->j]) & 255;
		msje[k] = (msje[k] ^ (self->s_box[t]));
		if (!self->is_crypter) {
			printf("%c", msje[k]);
		}
	}
}

void rc4_run(rc4_t* self, unsigned char* msje, int size) {
	if (size < 0) {
		printf("Error, el mensaje a codificar es inválido\n");
	} else if (self->key == NULL) {
		printf("Error, la clave de codificacion es incorrecta\n");
	} else {
		rc4_code(self, msje, size);
	}
}
