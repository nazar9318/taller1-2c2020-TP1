#include "common_encoder.h"

int encoder_create(encoder_t* self, char* method, char* key, bool is) {
	self->protocol = NULL;
	if (strcmp(method, "cesar") == 0) {
		self->mode = CESAR;
		self->protocol = (void*)cesar_create(key, is);
	} else if (strcmp(method, "vigenere") == 0) {
		self->mode = VIGENERE;
		self->protocol = (void*)vigenere_create(key, is);
	} else if (strcmp(method, "rc4") == 0) {
		self->mode = RC4;
		self->protocol = (void*)rc4_create(key, is);
	} else {
		return -1;
	}
	if (self->protocol == NULL) {
		printf("Encoder: Fallo al crear codificador\n");
		return -1;
	}
	return 0;
}

int encoder_run(encoder_t* self, unsigned char* msje, int len) {
	switch (self->mode) {
		case CESAR:
			cesar_run((cesar_t*)self->protocol, msje, len);
			return 0;
		case VIGENERE:
			vigenere_run((vigenere_t*)self->protocol, msje, len);
			return 0;
		case RC4:
			rc4_run((rc4_t*)self->protocol, msje, len);
			return 0;
		default:
			printf("Encoder: El metodo de codificacion provisto es incorrecto\n");
			return -1;
	}
}

int encoder_destroy(encoder_t* self) {
	if (self->protocol != NULL) {
		free(self->protocol);
		return 0;
	}
	return -1;
}
