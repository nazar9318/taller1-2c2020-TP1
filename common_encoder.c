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

unsigned char* rC4(encoder_t* encoder, unsigned char* msje, size_t size) {
	unsigned char s_box[256];
	char *key = encoder->key;
	unsigned int i;
	for (i = 0; i < 256; i++) {
		s_box[i] = i;
	}
	unsigned int j = 0;
	char aux;
	for (i = 0; i < 256; i++) {
		j = (j + s_box[i] + key[i % strlen(key)]) % 256;
		aux = s_box[i];
		s_box[i] = s_box[j];
		s_box[j] = aux;
	}
	i = 0;
	j = 0;
	for (int k = 0; k < size; k++) {
		i = (i + 1) % 256;
		j = (j + s_box[i]) % 256;
		aux = s_box[i];
		s_box[i] = s_box[j];
		s_box[j] = aux;	
		unsigned int t = (s_box[i] + s_box[j]) % 256;
		msje[k] = (msje[k] ^ (s_box[t]));
	}
	return msje;
}

unsigned char* encript(encoder_t* encoder, unsigned char* msje, int size) {
	if (size < 0) {
		printf("Error, el mensaje a codificar es inválido\n");
		return NULL;
	} else {
		if (encoder->key == NULL) {
			printf("Error, la clave de codificacion es incorrecta\n");
			return NULL;
		} else {
			if (strcmp(encoder->method, "cesar") == 0) {
				return cesar(encoder, msje, size);
			} else if (strcmp(encoder->method, "vigenere") == 0) {
				return vigenere(encoder, msje, size);
			} else if (strcmp(encoder->method, "rc4") == 0) {
				return rC4(encoder, msje, size);
			} else {
				printf("El metodo de codificacion provisto es incorrecto\n");
				return NULL;
			}
		}
	}
	printf("Error, el mensaje a codificar es inválido\n");
	return NULL;
}

void destruirEncoder(encoder_t* encoder) {
    free(encoder);
}

