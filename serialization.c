#include "serialization.h"

serialized_buffer_t *init_buffer_size(int size)
{
    if (size <= 0)
        return NULL;

    serialized_buffer_t *s_buffer = (serialized_buffer_t *)malloc(sizeof(serialized_buffer_t));
    s_buffer->buffer = malloc(size);
    s_buffer->size = size;
    s_buffer->seek_index = 0;

    return s_buffer;
}

serialized_buffer_t *init_buffer()
{
    return init_buffer_size(BUFFER_SIZE);
}

int get_buffer_available_size(serialized_buffer_t *serialized_buffer)
{
    return serialized_buffer->size - serialized_buffer->seek_index;
}

void resize_buffer(serialized_buffer_t *serialized_buffer, int type_size)
{
    int buffer_available_size = get_buffer_available_size(serialized_buffer);
    int is_resize_needed = false;

    // Loop needed because of custom buffer size
    while (buffer_available_size < type_size)
    {
        is_resize_needed = true;
        serialized_buffer->size = serialized_buffer->size * 2;
        buffer_available_size = get_buffer_available_size(serialized_buffer);
    };

    if (is_resize_needed)
        serialized_buffer->buffer = realloc(serialized_buffer->buffer, serialized_buffer->size);
}

void serialize_data(serialized_buffer_t *serialized_buffer, void *data, int type_size)
{
    // Will resize the buffer if needed
    resize_buffer(serialized_buffer, type_size);

    // Just copy the data into buffer
    memcpy((char *)serialized_buffer->buffer + serialized_buffer->seek_index, data, type_size);
    serialized_buffer->seek_index += type_size;
}

void unserialize_data(void *destination, serialized_buffer_t *serialize_buffer, int type_size)
{
    if (destination == NULL)
        return;

    int buffer_available_size = get_buffer_available_size(serialize_buffer);

    if (buffer_available_size < type_size)
        return;

    memcpy(destination, (char *)serialize_buffer->buffer + serialize_buffer->seek_index, type_size);
    serialize_buffer->seek_index += type_size;
}

void reset_seek(serialized_buffer_t *serialized_buffer)
{
    serialized_buffer->seek_index = 0;
}

void free_buffer(serialized_buffer_t *serialized_buffer)
{
    free(serialized_buffer->buffer);
    free(serialized_buffer);
}
