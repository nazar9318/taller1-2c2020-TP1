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
	bool es_server;
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

//Funcion: Envia mensaje de tamaño size al file_descriptor 
//con el que está conectado.
//Pre condicion: Socket previamente conectado.
//Post condicion: Devuelve 0 si no hubo error, -1 si lo hubo.
int enviarMensaje(socket_t* socket, unsigned char* mensaje, size_t size);

//Funcion: El server recibe el mensaje del cliente
//Pre condicion: Socket previamente creado.
//Post condicion: Devuelve la cantidad de bytes recibidos.
int recibirMensaje(socket_t* socket, unsigned char** mensaje);

//Funcion: Acepta el socket con el que se quiere comunicar,
//creando uno nuevo.
//Pre condicion: Socket previamente creado.
//Post condicion: Devuelve el socket aceptado.
socket_t* aceptar(socket_t* socket);

//Funcion: Server recibe y acepta una conexion del cliente
//Pre condicion: Socket previamente creado.
//Post condicion: Devuelve 0 si no hubo error, -1 si lo hubo.
int escuchar(socket_t* abstract_socket);

#endif