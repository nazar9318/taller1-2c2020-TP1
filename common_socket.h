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
	bool is_server;
}socket_t;

//Funcion: Crea un tipo de dato socket
//Pre condicion: El puerto y el host deben
//existir previamente y deben estar correctamente escritos
//Post condicion: Devuelve un puntero al socket
void socket_create(socket_t* self, char* host, char* port, bool is);

//Funcion: Envia mensaje de tamaño size al file_descriptor 
//con el que está conectado.
//Pre condicion: Socket previamente conectado.
//Post condicion: Devuelve 0 si no hubo error, -1 si lo hubo.
int socket_send(socket_t* self, unsigned char* mensaje, size_t size);

//Funcion: El server recibe el mensaje del cliente
//Pre condicion: Socket previamente creado.
//Post condicion: Devuelve la cantidad de bytes recibidos.
int socket_receive(socket_t* self, unsigned char* mensaje, size_t len);

//Funcion: Acepta el socket con el que se quiere comunicar,
//creando uno nuevo.
//Pre condicion: Socket previamente creado.
//Post condicion: Devuelve el socket aceptado.
void socket_accept(socket_t* accepted, socket_t* socket);

//Funcion: Server recibe y acepta una conexion del cliente
//Pre condicion: Socket previamente creado.
//Post condicion: Devuelve 0 si no hubo error, -1 si lo hubo.
int socket_listen(socket_t* self);

//Funcion: Destruye el socket
//Pre condicion: Socket previamente creado
//Post condicion: Memoria reservada liberada
void socket_destroy(socket_t* self);

#endif