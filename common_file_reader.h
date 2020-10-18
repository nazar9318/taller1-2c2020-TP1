#ifndef COMMON_FILE_READER_H
#define COMMON_FILE_READER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    FILE* file;
    size_t tamanio;
    char* buffer;
}file_reader_t;

//Funcion: Crea un tipo de dato file_reder.
//Pre condicion: File previamente abierto.
//Post condicion: Devuelve una referencia al file reader creado.
file_reader_t* crearFileReader(FILE* file);

//Funcion: Devuelve la lectura completa del archivo.
//Pre condicion: File_reader previamente creado.
//Post condicion: Devuelve un arreglo de unsigned chars
unsigned char* getRead(file_reader_t* reader);

//Funcion: Devuelve el tamanio de la lectura
//Pre condicion: File_reader previamente creado.
//Post condicion: Ninguna
size_t getSize(file_reader_t* crearFileReader);

//Funcion: Libera la memoria reservada para el file reader
//Pre condicion: File_reader previamente creado.
//Post condicion: Memoria liberada.
void destruirFileReader(file_reader_t* file_reader);

#endif
