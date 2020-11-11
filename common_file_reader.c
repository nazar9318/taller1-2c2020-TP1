#include "common_file_reader.h"

int reader_readFile(reader_t* self, unsigned char* buffer) {
	size_t read = fread(buffer, 1, self->tamanio, self->file);
	if (ferror(self->file) != 0) {
		printf("File_reader: Error al leer archivo");
		self->tamanio = -1;
	} else {
		self->tamanio = read;
	}
	return read;
}

void reader_create(reader_t* self, FILE* file) {
    self->file = file;
    self->tamanio = 64;
}

bool reader_EOF(reader_t* self) {
	return feof(self->file);
}

void reader_destroy(reader_t* self) {}
