#ifndef _SERIALIZATION_H_
#define _SERIALIZATION_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 512

typedef struct
{
    void *buffer;
    int size;
    int seek_index;
} serialized_buffer_t;


serialized_buffer_t *init_buffer_size(int size);
serialized_buffer_t* init_buffer();

int get_buffer_available_size(serialized_buffer_t *serialized_buffer);

void resize_buffer(serialized_buffer_t* serialized_buffer, int type_size);

void serialize_data(serialized_buffer_t *serialized_buffer, void *data, int type_size);
void unserialize_data(void* destination, serialized_buffer_t *serialize_buffer, int type_size);

void reset_seek(serialized_buffer_t *serialized_buffer);

void free_buffer(serialized_buffer_t *serialized_buffer);

#endif