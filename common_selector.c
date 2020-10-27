#include "common_selector.h"

selector_t* selector_create(char* arg_method, char* arg_key) {
	selector_t* selector = malloc(sizeof(selector_t));
	selector->method = NULL;
	selector->key = NULL;
	if (strncmp(arg_method, "--method=", 9) == 0) {
		selector->method = strchr(arg_method, '=');
	}
	if (strncmp(arg_key, "--key=", 6) == 0) {
		selector->key = strchr(arg_key, '=');
	}
	return selector;
}

char* selector_getMethod(selector_t* self) {
	return self->method+1;
}

char* selector_getKey(selector_t* self) {
	return self->key+1;
}

void selector_destroy(selector_t* selector) {
	free(selector);
}
