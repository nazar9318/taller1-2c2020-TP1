#include "common_rc4.h"

void rc4_create(rc4_t* self, char* method, char* key, bool is_crypter) {
	self->key = key;
	self->method = method;
	self->is_crypter = is_crypter;
}

static void rc4_swap(unsigned char* s_box, unsigned int pos_a, unsigned int pos_b) {
	unsigned char aux;
	aux = s_box[pos_a];
	s_box[pos_a] = s_box[pos_b];
	s_box[pos_b] = aux;
}

static void rc4_codeSBOX(unsigned char* s_box, char* key) {
	unsigned int j = 0;
	for (unsigned int i = 0; i < 256; i++) {
		j = (j + s_box[i] + key[i % strlen(key)]) % 256;
		rc4_swap(s_box, i, j);
	}
}

static void rc4_initializeSBOX(unsigned char* s_box) {
	for (unsigned int i = 0; i < 256; i++) {
		s_box[i] = i;
	}
}

static void rc4_code(rc4_t* self, unsigned char* msje, size_t size) {
	unsigned char s_box[256];
	rc4_initializeSBOX(s_box);
	rc4_codeSBOX(s_box, self->key);
	unsigned int i = 0;
	unsigned int j = 0;
	for (int k = 0; k < size; k++) {
		i = (i + 1) % 256;
		j = (j + s_box[i]) % 256;
		rc4_swap(s_box, i, j);
		unsigned int t = (s_box[i] + s_box[j]) % 256;
		msje[k] = (msje[k] ^ (s_box[t]));
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

void rc4_destroy(rc4_t* encoder) {}
