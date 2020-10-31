#ifndef COMMON_FILE_READER_H
#define COMMON_FILE_READER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    FILE* file;
    size_t tamanio;
}reader_t;

//Funcion: Crea un tipo de dato file_reder.
//Pre condicion: File previamente abierto.
//Post condicion: Ninguna
void reader_create(reader_t* reader, FILE* file);

//Funcion: Lee el archivo de tributo del reader
//y lo copia en buffer
//Pre condicion: File_reader previamente creado
//Post condicion: Ninguna
void reader_readFile(reader_t* self, unsigned char* buffer);

//Funcion: Devuelve si se llegó al final del archivo
//Pre condicion: File_reader previamente creado
//Post condicion: Ninguna
bool reader_EOF(reader_t* self);

//Funcion: Devuelve el tamanio de la lectura
//Pre condicion: File_reader previamente creado
//Post condicion: Reader previamente creado
size_t reader_getRead(reader_t* self);

#endif
