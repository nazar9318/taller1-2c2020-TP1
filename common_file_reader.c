#include "common_file_reader.h"

void leerArchivo(file_reader_t* file_reader) {
	int buff = file_reader->tamanio;
	if(fgets(file_reader->buffer, buff, file_reader->file) != NULL) {
		if ((strchr(file_reader->buffer, '\n')==NULL)&&(!feof(file_reader->file))) {
			while (strchr(file_reader->buffer, '\n') == NULL && !feof(file_reader->file)) {
				fseek(file_reader->file, -(buff-1), SEEK_CUR);
				buff+=32;
				file_reader->buffer = realloc(file_reader->buffer, buff);
				file_reader->buffer = fgets(file_reader->buffer, buff, file_reader->file);
			}
		}
	} else {
		free(file_reader->buffer);
		file_reader->buffer = NULL;
	}
	file_reader->tamanio = strlen(file_reader->buffer);
}

file_reader_t* crearFileReader(FILE* file) {
    file_reader_t* file_reader = malloc(sizeof(file_reader_t));
    file_reader->file = file;
    file_reader->tamanio = 64;
    file_reader->buffer = calloc(file_reader->tamanio, sizeof(char));
    leerArchivo(file_reader);
    return file_reader;
}

char* getRead(file_reader_t* file_reader) {
	return file_reader->buffer;
}

size_t getSize(file_reader_t* file_reader) {
	return file_reader->tamanio;
}

void destruirFileReader(file_reader_t* file_reader) {
    fclose(file_reader->file);
    free(file_reader->buffer);
    free(file_reader);
}

