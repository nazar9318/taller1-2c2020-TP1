#include "common_selector.h"
#define METH_LEN 9
#define KEY_LEN 6

selector_t* crearSelector(char* arg_method, char* arg_key) {
	selector_t* selector = malloc(sizeof(selector_t));
	selector->key = NULL;
	selector->method = NULL;
	if (strstr(arg_method, "--method=") != NULL) {
		selector->method = calloc(strlen(arg_method) - METH_LEN+1, sizeof(char));
		strncpy(selector->method, arg_method+METH_LEN, strlen(arg_method) - METH_LEN);
	}
	if (strstr(arg_key, "--key=") != NULL) {
		selector->key = calloc(strlen(arg_key) - KEY_LEN+1, sizeof(char));
		strncpy(selector->key, arg_key + KEY_LEN, strlen(arg_key) -KEY_LEN);
	}
	return selector;
}

char* devolverMetodo(selector_t* selector) {
	return selector->method;
}

char* devolverClave(selector_t* selector) {
	return selector->key;
}

void destruirSelector(selector_t* selector) {
	free(selector->method);
	free(selector->key);
	free(selector);
}
