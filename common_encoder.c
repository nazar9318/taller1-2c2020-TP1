#include "common_encoder.h"

encoder_t* crearEncoder(char* method, char* key, bool es_encriptador) {
    encoder_t* encoder = malloc(sizeof(encoder_t));
    encoder->key = key;
    encoder->method = method;
    encoder->es_encriptador = es_encriptador;
    return encoder;
}

char* codificarCesar(encoder_t* encoder, char* mensaje, size_t tamanio) {
    int key_int = atoi(encoder->key) * (encoder->es_encriptador ? 1 : -1);
    for (int i = 0; i < tamanio; i++) {
        mensaje[i] += key_int;
    }
    return mensaje;
}

char* codificarVigenere(encoder_t* encoder, char* mensaje, size_t tamanio) {
    size_t buff_key = 0;
    int tipo_codificacion = encoder->es_encriptador ? 1 : -1;
    for (int i = 0; i < tamanio; i++) {
        if ((i + buff_key) >= strlen(encoder->key)) {
            buff_key -= strlen(encoder->key);
        }
        mensaje[i] += ((encoder->key[i + buff_key]) * tipo_codificacion);
    }
    return mensaje;
}

char* codificar(encoder_t* encoder, char* mensaje, int tamanio_mensaje) {
    if (tamanio_mensaje < 0) {
    	printf("Error, el mensaje a codificar es inválido\n");
	    return NULL;
    } else {
	 if (strcmp(encoder->method, "cesar") == 0) {
		return codificarCesar(encoder, mensaje, tamanio_mensaje);
	 } else if (strcmp(encoder->method, "vigenere") == 0) {
		return codificarVigenere(encoder, mensaje, tamanio_mensaje);
	 }
    }
    printf("Error, el mensaje a codificar es inválido\n");
    return NULL;
}

void destruirEncoder(encoder_t* encoder) {
    free(encoder);
}
