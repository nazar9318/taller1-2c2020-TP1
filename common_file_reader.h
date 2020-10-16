#ifndef COMMON_FILE_READER_H
#define COMMON_FILE_READER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    FILE* file;
    size_t tamanio;
    char* buffer;
}file_reader_t;

file_reader_t* crearFileReader(FILE* file);

char* getRead(file_reader_t* reader);

size_t getSize(file_reader_t* crearFileReader);

void destruirFileReader(file_reader_t* file_reader);

#endif
