#include "common_file_reader.h"

void reader_readFile(reader_t* self, unsigned char* buffer) {
	size_t read = fread(buffer, 1, self->tamanio, self->file);
	self->tamanio = read;
}

void reader_create(reader_t* reader, FILE* file) {
    reader->file = file;
    reader->tamanio = 64;
}

bool reader_EOF(reader_t* file_reader) {
	return feof(file_reader->file);
}

size_t reader_getRead(reader_t* self) {
	return self->tamanio;
}

void reader_destroy(reader_t* file_reader) {}
