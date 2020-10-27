#ifndef COMMON_FILE_READER_H
#define COMMON_FILE_READER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    FILE* file;
    size_t tamanio;
    char* buffer;
}reader_t;

//Funcion: Crea un tipo de dato file_reder.
//Pre condicion: File previamente abierto.
//Post condicion: Devuelve una referencia al file reader creado.
reader_t* reader_create(FILE* file);

//Funcion: Devuelve la lectura completa del archivo.
//Pre condicion: File_reader previamente creado.
//Post condicion: Devuelve un arreglo de unsigned chars
unsigned char* reader_getRead(reader_t* self);

//Funcion: Devuelve el tamanio de la lectura
//Pre condicion: File_reader previamente creado.
//Post condicion: Ninguna
size_t reader_getSize(reader_t* self);

//Funcion: Libera la memoria reservada para el file reader
//Pre condicion: File_reader previamente creado.
//Post condicion: Memoria liberada.
void reader_destroy(reader_t* self);

#endif
