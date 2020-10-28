#define _POSIX_C_SOURCE 200112L
#include "common_socket.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

//Funcion: Enlaza al socket con la direccion pasada por parametro
//Pre condicion: Ninguna.
//Post condicion: Si falla al enlazar cierra el file descriptor
static int socket_bind(socket_t* socket, struct addrinfo* dir) {
	int fd = socket->fd;
	if (bind(fd, dir->ai_addr, dir->ai_addrlen) == -1) {
		printf("Error, servidor no pudo enlazar: %s\n", strerror(errno));
		close(socket->fd);
		return -1;
	}
	return 0;
}

//Funcion: Conecta al socket con la direccion pasada por parametro
//Pre condicion: Ninguna.
//Post condicion: Si falla al enlazar cierra el file descriptor
static int socket_connect(socket_t* socket, struct addrinfo* dir) {
	int fd = socket->fd;
	if (connect(fd, dir->ai_addr, dir->ai_addrlen) == -1) {
		printf("Error, cliente no pudo conectar: %s\n", strerror(errno));
		close(socket->fd);
		return -1;
	}
	return 0;
}

static socket_t* socket_bindConnect(socket_t* sckt, struct addrinfo* dir) {
	if (sckt->es_server) {
		if (socket_bind(sckt, dir) == 0) {
			freeaddrinfo(dir);
			return sckt;
		}
	} else {
		if (socket_connect(sckt, dir) == 0) {
			freeaddrinfo(dir);
			return sckt;
		}
	}
	freeaddrinfo(dir);
	free(sckt);
	return NULL;
}

//Funcion: crea el socket usando las direcciones pasadas por parametro.
//Pre condicion: Ninguna.
//Post condicion: En caso de fallar devuelve NULL
static socket_t* socket_setFileDesc(socket_t* sckt, struct addrinfo *dirs) {
	struct addrinfo *count = NULL;
	count = dirs;
	while (count != NULL) {
		sckt->fd = socket(count->ai_family,count->ai_socktype,count->ai_protocol);
		if (socket_bindConnect(sckt, count) == NULL) {
			close(sckt->fd);
			free(sckt);
			count = count->ai_next;
		} else {
			return sckt;
		}
	}
	return NULL;
}

//Funcion: Completa los criterios de direccion para un server
//Pre condicion: Ninguna
//Post condicion: Ninguna
static struct addrinfo socket_setAddressCriteria(bool es_server) {
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
static struct addrinfo* socket_setDirs(char* host, char* port, bool is) {
	int error = 0;
	struct addrinfo criteria = socket_setAddressCriteria(is);
	struct addrinfo *direcciones;
	error = getaddrinfo(host, port, &criteria, &direcciones);
	if (error != 0) {
		printf("No se pudieron crear las direcciones para el socket");
		freeaddrinfo(direcciones);
		return NULL;
	}
	return direcciones;
}

socket_t* socket_setAccepted(int file_descriptor) {
	socket_t* socket = malloc(sizeof(socket_t));
	if (socket == NULL) {
		printf("Error al alocar memoria para crear el socket aceptado\n");
		return NULL;
	}
	socket->fd = file_descriptor;
	return socket;
}

socket_t* socket_create(char* host, char* puerto, bool es_server) {
	socket_t* socket = malloc(sizeof(socket_t));
	if (socket == NULL) {
		printf("Error al alocar memoria para crear el socket\n");
		return NULL;
	}
	socket->es_server = es_server;
	struct addrinfo *direcciones = NULL;
	direcciones = socket_setDirs(host, puerto, socket->es_server);
	if (direcciones != NULL) {
		return socket_setFileDesc(socket, direcciones);
	}
	freeaddrinfo(direcciones);
	free(socket);
	return NULL;
}

int socket_send(socket_t* self, unsigned char* mensaje, size_t size) {
	return send(self->fd, mensaje, size, MSG_NOSIGNAL);
}

int socket_receive(socket_t* self, unsigned char* mensaje, size_t len) {
	return recv(self->fd, mensaje, len, 0);
}

socket_t* socket_accept(socket_t* socket) {
	int fd = socket->fd;
	int aceptado;
	aceptado = accept(fd, NULL, NULL);
	if (aceptado == -1) {
		printf("Error, servidor no puede aceptar al cliente: %s\n", strerror(errno));
		socket_destroy(socket);
		return NULL;
	}
	return socket_setAccepted(aceptado);
}

int socket_listen(socket_t* socket) {
	int fd = socket->fd;
	if (listen(fd, 1) == -1) {
		printf("Error, servidor no puede escuchar al cliente: %s\n", strerror(errno));
		socket_destroy(socket);
		return -1;
	} 
	return 0;
}

void socket_destroy(socket_t* socket) {
	if (socket != NULL) {
		close(socket->fd);
	}
	free(socket);
}