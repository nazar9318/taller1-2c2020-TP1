#include "common_rc4.h"
#include <errno.h>

static void rc4_swap(rc4_t* self, unsigned int a, unsigned int b) {
	unsigned char aux;
	aux = self->s_box[a];
	self->s_box[a] = self->s_box[b];
	self->s_box[b] = aux;
}

static void rc4_initializeSBOX(rc4_t* self) {
	for (int i = 0; i < 256; i++) {
		self->s_box[i] = i;
	}
	int j = 0;
	for (int i = 0; i < 256; i++) {
		j = (j + self->s_box[i] + self->key[i % strlen(self->key)]) & 255;
		rc4_swap(self, i, j);
	}
}

rc4_t* rc4_create(char* key, bool is_crypter) {
	rc4_t* self = malloc(sizeof(rc4_t));
	if (self != NULL) {
		self->key = key;
		self->is_crypter = is_crypter;
		rc4_initializeSBOX(self);
		self->i = 0;
		self->j = 0;	
	} else {
		printf("RC4: Fallo al alocar memoria para rc4 %s\n", strerror(errno));
	}
	return self;
}

static unsigned char rc4_output(rc4_t* self) {
	self->i = (self->i + 1) % 256;
	self->j = (self->j + self->s_box[self->i]) % 256;
	rc4_swap(self, self->i, self->j);
	return self->s_box[(self->s_box[self->i] + self->s_box[self->j]) % 256];
}

static void rc4_code(rc4_t* self, unsigned char* msje, size_t size) {
	for (int k = 0; k < size; k++) {
		msje[k] = msje[k] ^ rc4_output(self);
		if (!self->is_crypter) {
			printf("%c", msje[k]);
		}
	}
}

void rc4_run(rc4_t* self, unsigned char* msje, int size) {
	if (size < 0) {
		printf("RC4: Error, el mensaje a codificar es inválido\n");
	} else if (self->key == NULL) {
		printf("RC4: Error, la clave de codificacion es incorrecta\n");
	} else {
		rc4_code(self, msje, size);
	}
}

void rc4_destroy(rc4_t* self) {}
