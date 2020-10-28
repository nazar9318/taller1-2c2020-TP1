#include "common_file_reader.h"

unsigned char* reader_readFile(reader_t* self) {
	size_t buff = self->tamanio;
	FILE* file = self->file;
	size_t read = fread(self->buffer, 1, buff, file);
	if (read == 0) {
		self->buffer = NULL;
		return NULL;
	} else if (read < 64){
		self->buffer[read] = '\0';
	}
	self->tamanio = read;
	return self->buffer;
}

void reader_create(reader_t* reader, FILE* file) {
    reader->file = file;
    reader->tamanio = 64;
    reader->buffer = calloc(reader->tamanio, sizeof(char));
	if (reader == NULL) {
		printf("Fallo al alocar memoria para el buffer del file reader\n");
		reader_destroy(reader);
	}
}

bool reader_EOF(reader_t* file_reader) {
	return feof(file_reader->file);
}

size_t reader_getRead(reader_t* self) {
	return self->tamanio;
}

void reader_destroy(reader_t* file_reader) {
	if (file_reader->file != NULL) {
		fclose(file_reader->file);
	}
	if (file_reader->buffer != NULL) {
		free(file_reader->buffer);
	}
}
