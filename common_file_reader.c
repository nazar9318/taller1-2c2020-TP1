#include "common_file_reader.h"

void leerArchivo(file_reader_t* file_reader) {
	size_t buff = file_reader->tamanio;
	FILE* file = file_reader->file;
	size_t read = fread(file_reader->buffer, 1, buff, file);
	if(read == buff) {
		while (!feof(file)) {
			fseek(file, 0, SEEK_SET);
			buff+=64;
			free(file_reader->buffer);
			file_reader->buffer = calloc(buff, sizeof(char));
			read = fread(file_reader->buffer, 1, buff, file);
		}
	} else if (!feof(file)) {
		free(file_reader->buffer);
		file_reader->buffer = NULL;
	}
	file_reader->tamanio = read;
}

file_reader_t* crearFileReader(FILE* file) {
    file_reader_t* file_reader = malloc(sizeof(file_reader_t));
    file_reader->file = file;
    file_reader->tamanio = 64;
    file_reader->buffer = calloc(file_reader->tamanio, sizeof(char));
    leerArchivo(file_reader);
    return file_reader;
}

unsigned char* getRead(file_reader_t* file_reader) {
	return (unsigned char*)file_reader->buffer;
}

size_t getSize(file_reader_t* file_reader) {
	return file_reader->tamanio;
}

void destruirFileReader(file_reader_t* file_reader) {
    fclose(file_reader->file);
    free(file_reader->buffer);
    free(file_reader);
}
