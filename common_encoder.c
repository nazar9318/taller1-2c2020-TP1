#include "common_encoder.h"

void encoder_create(encoder_t* self, char* method, char* key, bool is) {
	self->key = key;
	self->method = method;
	self->is_crypter = is;
	if (strcmp(self->method, "cesar") == 0) {
		self->mode = CESAR;
		self->protocol = (void*)cesar_create(self->key, self->is_crypter);
	} else if (strcmp(self->method, "vigenere") == 0) {
		self->mode = VIGENERE;
		self->protocol = (void*)vigenere_create(self->key, self->is_crypter);
	} else if (strcmp(self->method, "rc4") == 0) {
		self->mode = RC4;
		self->protocol = (void*)rc4_create(self->key, self->is_crypter);
	} else {
		printf("El metodo de codificacion provisto es incorrecto\n");
	}
}

static void encoder_choose(encoder_t* self, unsigned char* msje, int len) {
	if (strcmp(self->method, "cesar") == 0) {
		cesar_run((cesar_t*)self->protocol, msje, len);
	} else if (strcmp(self->method, "vigenere") == 0) {
		vigenere_run((vigenere_t*)self->protocol, msje, len);
	} else if (strcmp(self->method, "rc4") == 0) {
		rc4_run((rc4_t*)self->protocol, msje, len);
	} else {
		printf("El metodo de codificacion provisto es incorrecto\n");
	}
}

void encoder_run(encoder_t* self, unsigned char* msje, int size) {
	if (size < 0) {
		printf("Error, el mensaje a codificar es inválido\n");
	} else if (self->key == NULL) {
		printf("Error, la clave de codificacion es incorrecta\n");
	} else {
		encoder_choose(self, msje, size);
	}
}

void encoder_destroy(encoder_t* self) {
	free(self->protocol);
}
