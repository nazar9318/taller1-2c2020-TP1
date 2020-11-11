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
	freeaddrinfo(dir);
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
	freeaddrinfo(dir);
	return 0;
}

static int socket_bindConnect(socket_t* sckt, struct addrinfo* dir) {
	return sckt->is_server ? socket_bind(sckt, dir) : socket_connect(sckt, dir);
}

//Funcion: crea el socket usando las direcciones pasadas por parametro.
//Pre condicion: Ninguna.
//Post condicion: En caso de fallar devuelve NULL
static int socket_setFileDesc(socket_t* sckt, struct addrinfo *dirs) {
	struct addrinfo *count = dirs;
	while (count != NULL) {
		sckt->fd = socket(count->ai_family,count->ai_socktype,count->ai_protocol);
		if (socket_bindConnect(sckt, count) == -1) {
			close(sckt->fd);
			count = count->ai_next;
		} else {
			return 0;
		}
	}
	printf("Fallo al conectar al socket\n");
	return -1;
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
		printf("No se pudo crear la dirección para el socket %s\n", strerror(errno));
		freeaddrinfo(direcciones);
		return NULL;
	}
	return direcciones;
}

int socket_create(socket_t* self, char* host, char* port, bool is) {
	self->is_server = is;
	struct addrinfo *direcciones;
	direcciones = socket_setDirs(host, port, self->is_server);
	if (direcciones != NULL) {
		return socket_setFileDesc(self, direcciones);
	}
	return -1;
}

int socket_send(socket_t* self, unsigned char* mensaje, size_t size) {
	int total = 0;
	while (total < size) {
		int sent = send(self->fd, mensaje + total, size - total, MSG_NOSIGNAL);
		if (sent == -1) {
			return -1;
		} else {
			total += sent;
		}
	}
	return total;
}

int socket_receive(socket_t* self, unsigned char* mensaje, size_t len) {
	int received = 0;
	int total = 0;
	do {
		received = recv(self->fd, mensaje + total, len - total, 0);
		if (received == -1) {
			return -1;
		} else {
			total += received;
		}
	} while (received > 0 && total < len);
	return total;
}

int socket_accept(socket_t* accepted, socket_t* self) {
	int aceptado = accept(self->fd, NULL, NULL);
	if (aceptado == -1) {
		printf("Error, servidor no puede aceptar al cliente: %s\n", strerror(errno));
		socket_destroy(self);
		return -1;
	}
	accepted->fd = aceptado;
	return 0;
}

int socket_listen(socket_t* self) {
	int fd = self->fd;
	if (listen(fd, 1) == -1) {
		printf("Error, servidor no puede escuchar al cliente: %s\n", strerror(errno));
		socket_destroy(self);
		return -1;
	} 
	return 0;
}

int socket_destroy(socket_t* self) {
	return close(self->fd);
}
