#include "common_encoder.h"

encoder_t* encoder_create(char* method, char* key, bool es_encriptador) {
	encoder_t* encoder = malloc(sizeof(encoder_t));
	encoder->key = key;
	encoder->method = method;
	encoder->es_encriptador = es_encriptador;
	return encoder;
}

static unsigned char* encoder_cesar(encoder_t* self, unsigned char* msje, size_t len) {
	bool es_encriptador = self->es_encriptador;
	unsigned int u_key = (unsigned int) strtol(self->key, (char**) NULL,10);
	if (u_key == 0 && self->key[0] != '0') {
		//error
	}
	for (int i = 0; i < len; i++) {
		msje[i] += es_encriptador ? u_key : 256 - u_key;
	}
	return msje;
}

static unsigned char* encoder_vigenere(encoder_t* encoder, unsigned char* msje, size_t size) {
	size_t buff_key = 0;
	bool tipo = encoder->es_encriptador;
	for (int i = 0; i < size; i++) {
		if ((i + buff_key) >= strlen(encoder->key)) {
			buff_key -= strlen(encoder->key);
		}
		char key_char = encoder->key[i + buff_key];
		unsigned char buffer = tipo ? key_char : (256 - key_char);
		msje[i] += buffer;
	}
	return msje;
}

static void encoder_swap(unsigned char* s_box, unsigned int pos_a, unsigned int pos_b) {
	unsigned char aux;
	aux = s_box[pos_a];
	s_box[pos_a] = s_box[pos_b];
	s_box[pos_b] = aux;
}

static void encoder_codeSBOX(unsigned char* s_box, char* key) {
	unsigned int j = 0;
	for (unsigned int i = 0; i < 256; i++) {
		j = (j + s_box[i] + key[i % strlen(key)]) % 256;
		encoder_swap(s_box, i, j);
	}
}

static void encoder_initializeSBOX(unsigned char* s_box) {
	for (unsigned int i = 0; i < 256; i++) {
		s_box[i] = i;
	}
}

static unsigned char* encoder_rC4(encoder_t* encoder, unsigned char* msje, size_t size) {
	unsigned char s_box[256];
	encoder_initializeSBOX(s_box);
	encoder_codeSBOX(s_box, encoder->key);
	unsigned int i = 0;
	unsigned int j = 0;
	for (int k = 0; k < size; k++) {
		i = (i + 1) % 256;
		j = (j + s_box[i]) % 256;
		encoder_swap(s_box, i, j);
		unsigned int t = (s_box[i] + s_box[j]) % 256;
		msje[k] = (msje[k] ^ (s_box[t]));
	}
	return msje;
}

static unsigned char* encoder_choose(encoder_t* coder, unsigned char* msje, int len) {
	if (strcmp(coder->method, "cesar") == 0) {
		return encoder_cesar(coder, msje, len);
	} else if (strcmp(coder->method, "vigenere") == 0) {
		return encoder_vigenere(coder, msje, len);
	} else if (strcmp(coder->method, "rc4") == 0) {
		return encoder_rC4(coder, msje, len);
	}
	printf("El metodo de codificacion provisto es incorrecto\n");
	return NULL;
}

unsigned char* encoder_encode(encoder_t* self, unsigned char* msje, int size) {
	if (size < 0) {
		printf("Error, el mensaje a codificar es inválido\n");
		return NULL;
	} else if (self->key == NULL) {
		printf("Error, la clave de codificacion es incorrecta\n");
		return NULL;
	}
	return encoder_choose(self, msje, size);
}

void encoder_destroy(encoder_t* encoder) {
    free(encoder);
}
