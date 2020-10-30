#include "common_selector.h"

int selector_create(selector_t* self, char* argv_method, char* argv_key) {
	self->method = NULL;
	self->key = NULL;
	if (strncmp(argv_method, "--method=", 9) == 0) {
		self->method = strchr(argv_method, '=');
	} else {
		printf("Selector: El formato de entrada del método es inválido\n");
		return -1;
	}
	if (strncmp(argv_key, "--key=", 6) == 0) {
		self->key = strchr(argv_key, '=');
	} else {
		printf("Selector: El formato de entrada de la clave es inválida\n");
		return -1;
	}
	return 0;
}

char* selector_getMethod(selector_t* self) {
	return self->method+1;
}

char* selector_getKey(selector_t* self) {
	return self->key+1;
}
