#include "common_selector.h"

void selector_create(selector_t* self, char* argv_method, char* argv_key) {
	self->method = NULL;
	self->key = NULL;
	if (strncmp(argv_method, "--method=", 9) == 0) {
		self->method = strchr(argv_method, '=');
	}
	if (strncmp(argv_key, "--key=", 6) == 0) {
		self->key = strchr(argv_key, '=');
	}
}

char* selector_getMethod(selector_t* self) {
	return self->method+1;
}

char* selector_getKey(selector_t* self) {
	return self->key+1;
}

void selector_destroy(selector_t* selector) {}
