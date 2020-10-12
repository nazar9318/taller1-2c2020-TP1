#define _POSIX_C_SOURCE 200112L
#include "common_socket.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

void destruirSocket(socket_t* socket) {
	close(socket->file_descriptor);
	free(socket);
}

//Funcion: Enlaza al socket con la direccion pasada por parametro
//Pre condicion: Ninguna.
//Post condicion: Si falla al enlazar cierra el file descriptor
int enlazar(socket_t* socket, struct addrinfo* dir) {
	int fd = socket->file_descriptor;
	if (bind(fd, dir->ai_addr, dir->ai_addrlen) == -1) {
		printf("Error, servidor no pudo enlazar: %s\n", strerror(errno));
		close(socket->file_descriptor);
		return -1;
	}
	return 0;
}

//Funcion: Conecta al socket con la direccion pasada por parametro
//Pre condicion: Ninguna.
//Post condicion: Si falla al enlazar cierra el file descriptor
int conectar(socket_t* socket, struct addrinfo* dir) {
	int fd = socket->file_descriptor;
	if (connect(fd, dir->ai_addr, dir->ai_addrlen) == -1) {
		printf("Error, cliente no pudo conectar: %s\n", strerror(errno));
		close(socket->file_descriptor);
		return -1;
	}
	return 0;
}

//Funcion: crea el socket usando las direcciones pasadas por parametro.
//Pre condicion: Ninguna.
//Post condicion: En caso de fallar devuelve NULL
struct addrinfo* setFileDescriptor(socket_t* t_socket, struct addrinfo *dirs) {
	//int fd = -1;
	//bool connected = false;
	struct addrinfo *count = NULL;
	count = dirs;
	while (count != NULL) {//} && !connected) {
		int fd = socket(count->ai_family, count->ai_socktype, count->ai_protocol);
		if (fd == -1) {
			printf("Error, no se pudo crear el socket: %s\n", strerror(errno));
			return NULL;
		} else {
			t_socket->file_descriptor = fd;
			//connected = true;
			return count;
		}
		count = count->ai_next;
	}
	return count;
}

//Funcion: Completa los criterios de direccion para un server
//Pre condicion: Ninguna
//Post condicion: Ninguna
struct addrinfo setAddressCriteria(bool es_server) {
	struct addrinfo criteria;
	memset(&criteria, 0, sizeof(struct addrinfo));
	criteria.ai_family = AF_INET;		//Permite IPv4
	criteria.ai_socktype = SOCK_STREAM;	//Protocolo TCP
	criteria.ai_flags = es_server ? AI_PASSIVE : 0;
	return criteria;
}

//Funcion: Crea las direcciones con las que el server va a intentar conectarse
//Pre condicion: Puerto debe ser existente.
//Post condicion: Si getaddrinfo falla se libera la memoria, pero en caso 
//de tener exito debe ser el llamador el que libere la memoria reservada.
struct addrinfo* crearDirecciones(char* host, char* port, bool es_server) {
	int error = 0;
	struct addrinfo criteria = setAddressCriteria(es_server);
	struct addrinfo *direcciones;
	error = getaddrinfo(host, port, &criteria, &direcciones);
	if (error != 0) {
		printf("No se pudieron crear las direcciones para el socket");
		freeaddrinfo(direcciones);
		return NULL;
	}
	return direcciones;
}

socket_t* crearSocketAceptado(int file_descriptor) {
	socket_t* socket = malloc(sizeof(socket_t));
	socket->file_descriptor = file_descriptor;
	return socket;
}

socket_t* crearSocket(char* host, char* puerto, bool es_server) {
	socket_t* socket = malloc(sizeof(socket_t));
	struct addrinfo *direcciones = NULL;
	direcciones = crearDirecciones(host, puerto, es_server);
	if (direcciones != NULL) {
		struct addrinfo* direccion_aceptada = NULL;
		direccion_aceptada = setFileDescriptor(socket, direcciones);
		if (direccion_aceptada != NULL) {
			if (es_server) {
				if (enlazar(socket, direccion_aceptada) == 0) {
					freeaddrinfo(direcciones);
					return socket;
				}
			} else {
				if (conectar(socket, direccion_aceptada) == 0) {
					freeaddrinfo(direcciones);
					return socket;
				}
			}
		}
	}
	return NULL;
}

int enviarMensaje(socket_t* socket, char* mensaje, size_t tamanio) {
	int total = 0;
	//int sent = 0;
	int fd = socket->file_descriptor;
	while (total < tamanio) {
		//sent = send(fd, mensaje+total, tamanio, MSG_NOSIGNAL);
		//total += sent;
		total += send(fd, mensaje+total, tamanio, MSG_NOSIGNAL);
		/*if (sent == -1) {
			return -1;
		}*/
	}
	return 0;
}

int recibirMensaje(socket_t* socket, char* mensaje, size_t tamanio) {
	int received = 0;
	int total = 0;
	int fd = socket->file_descriptor;
	do {
		received = recv(fd, &mensaje[total], tamanio, 0);
		total += received;
		if (total > tamanio) {
			mensaje = realloc(mensaje, 64 + sizeof(mensaje));
		}
		/*if (received == -1) {
			return -1;
		}*/
	}while (received > 0);
	return total;
}

int escuchar(socket_t* socket) {
	int fd = socket->file_descriptor;
	if (listen(fd, 1) == -1) {
		printf("Error, servidor no puede escuchar al cliente: %s\n", strerror(errno));
		destruirSocket(socket);
		return -1;
	} 
	return 0;
}

socket_t* aceptar(socket_t* socket) {
	int fd = socket->file_descriptor;
	int aceptado;
	aceptado = accept(fd, NULL, NULL);
	if (aceptado == -1) {
		printf("Error, servidor no puede aceptar al cliente: %s\n", strerror(errno));
		destruirSocket(socket);
		return NULL;
	}
	return crearSocketAceptado(aceptado);
}
