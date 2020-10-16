#ifndef COMMON_SOCKET_H
#define COMMON_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int fd;
}socket_t;

//Funcion: Crea un tipo de dato socket
//Pre condicion: El puerto y el host deben
//existir previamente y deben estar correctamente escritos
//Post condicion: Devuelve un puntero al socket
socket_t* crearSocket(char* host, char* puerto, bool es_server);

//Funcion: Destruye el socket
//Pre condicion: Socket previamente creado
//Post condicion: Memoria reservada liberada
void destruirSocket(socket_t* socket);

int enviarMensaje(socket_t* socket, unsigned char* mensaje, size_t size);

//Funcion: El server recibe el mensaje del cliente
//Pre condicion: Ninguna
//Post condicion: Devuelve el arreglo binario completo,
//si se corto la comunicacion se devuelve NULL.
int recibirMensaje(socket_t* socket, unsigned char** mensaje);

socket_t* aceptar(socket_t* socket);

//Funcion: Server recibe y acepta una conexion del cliente
//Pre condicion: Ninguna
//Post condicion: Ninguna
int escuchar(socket_t* abstract_socket);

#endif

