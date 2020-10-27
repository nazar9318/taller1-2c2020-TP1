#include "common_file_reader.h"

static void reader_readFile(reader_t* self) {
	size_t buff = self->tamanio;
	FILE* file = self->file;
	size_t read = fread(self->buffer, 1, buff, file);
	if(read == buff) {
		while (!feof(file)) {
			fseek(file, 0, SEEK_SET);
			buff+=64;
			free(self->buffer);
			self->buffer = calloc(buff, sizeof(char));
			read = fread(self->buffer, 1, buff, file);
		}
	} else if (!feof(file)) {
		free(self->buffer);
		self->buffer = NULL;
	}
	self->tamanio = read;
}

reader_t* reader_create(FILE* file) {
    reader_t* file_reader = malloc(sizeof(reader_t));
    file_reader->file = file;
    file_reader->tamanio = 64;
    file_reader->buffer = calloc(file_reader->tamanio, sizeof(char));
    reader_readFile(file_reader);
    return file_reader;
}

unsigned char* reader_getRead(reader_t* file_reader) {
	return (unsigned char*)file_reader->buffer;
}

size_t reader_getSize(reader_t* file_reader) {
	return file_reader->tamanio;
}

void reader_destroy(reader_t* file_reader) {
    fclose(file_reader->file);
    free(file_reader->buffer);
	free(file_reader);
}

