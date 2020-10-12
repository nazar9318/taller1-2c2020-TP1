#include "common_mensaje.h"

mensaje_t* crearMensaje(char* mensaje) {
    mensaje_t* message = malloc(sizeof(mensaje_t));
    message->contenido = mensaje;
    return message;
}

size_t devolverTamanio(mensaje_t* message) {
    return strlen(message->contenido);
}

char* devolverMensaje(mensaje_t* message) {
    return message->contenido;
}

void destruirMensaje(mensaje_t* message) {
    free(message);
}
