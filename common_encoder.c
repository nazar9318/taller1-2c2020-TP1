#include "common_encoder.h"

encoder_t* crearEncoder(char* method, char* key, bool es_encriptador) {
	encoder_t* encoder = malloc(sizeof(encoder_t));
	encoder->key = key;
	encoder->method = method;
	encoder->es_encriptador = es_encriptador;
	return encoder;
}

unsigned char* cesar(encoder_t* encoder, unsigned char* msje, size_t size) {
	bool es_encriptador = encoder->es_encriptador;
	unsigned int u_key = (unsigned int) atoi(encoder->key);
	for (int i = 0; i < size; i++) {
		msje[i] += es_encriptador ? u_key : 256 - u_key;
	}
	return msje;
}

unsigned char* vigenere(encoder_t* encoder, unsigned char* msje, size_t size) {
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

void swap(unsigned char* s_box, unsigned int pos_a, unsigned int pos_b) {
	unsigned char aux;
	aux = s_box[pos_a];
	s_box[pos_a] = s_box[pos_b];
	s_box[pos_b] = aux;
}

void codificarSBOX(unsigned char* s_box, char* key) {
	unsigned int j = 0;
	for (unsigned int i = 0; i < 256; i++) {
		j = (j + s_box[i] + key[i % strlen(key)]) % 256;
		swap(s_box, i, j);
	}
}

void inicializarSBOX(unsigned char* s_box) {
	for (unsigned int i = 0; i < 256; i++) {
		s_box[i] = i;
	}
}

unsigned char* rC4(encoder_t* encoder, unsigned char* msje, size_t size) {
	unsigned char s_box[256];
	inicializarSBOX(s_box);
	codificarSBOX(s_box, encoder->key);
	unsigned int i = 0;
	unsigned int j = 0;
	for (int k = 0; k < size; k++) {
		i = (i + 1) % 256;
		j = (j + s_box[i]) % 256;
		swap(s_box, i, j);
		unsigned int t = (s_box[i] + s_box[j]) % 256;
		msje[k] = (msje[k] ^ (s_box[t]));
	}
	return msje;
}

unsigned char* elegirMetodo(encoder_t* coder, unsigned char* msje, int size) {
	if (strcmp(coder->method, "cesar") == 0) {
		return cesar(coder, msje, size);
	} else if (strcmp(coder->method, "vigenere") == 0) {
		return vigenere(coder, msje, size);
	} else if (strcmp(coder->method, "rc4") == 0) {
		return rC4(coder, msje, size);
	}
	printf("El metodo de codificacion provisto es incorrecto\n");
	return NULL;
}

unsigned char* codificar(encoder_t* encoder, unsigned char* msje, int size) {
	if (encoder->key == NULL) {
		printf("Error, la clave de codificacion es incorrecta\n");
		return NULL;
	}
	return elegirMetodo(encoder, msje, size);
}

unsigned char* encriptar(encoder_t* encoder, unsigned char* msje, int size) {
	if (size > 0) {
		return codificar(encoder, msje, size);
	}
	printf("Error, el mensaje a codificar es inválido\n");
	return NULL;
}

void destruirEncoder(encoder_t* encoder) {
    free(encoder);
}
