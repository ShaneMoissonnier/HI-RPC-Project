#include "serialization.h"

serialized_buffer_t *init_buffer()
{
    serialized_buffer_t *s_buffer = (serialized_buffer_t *)malloc(sizeof(serialized_buffer_t));
    s_buffer->buffer = malloc(BUFFER_SIZE);
    s_buffer->size = BUFFER_SIZE;
    s_buffer->seek_index = 0;

    return s_buffer;
}

serialized_buffer_t *init_buffer_size(int size)
{
    serialized_buffer_t *s_buffer = (serialized_buffer_t *)malloc(sizeof(serialized_buffer_t));
    s_buffer->buffer = malloc(size);
    s_buffer->size = size;
    s_buffer->seek_index = 0;

    return s_buffer;
}

void resize_buffer(serialized_buffer_t *serialized_buffer, int type_size)
{
    int available_space = serialized_buffer->size - serialized_buffer->seek_index;
    int is_resize_needed = false;

    // Loop needed because of custom buffer size
    while (available_space < type_size)
    {
        serialized_buffer->size = serialized_buffer->size * 2;
        available_space = serialized_buffer->size - serialized_buffer->seek_index;
        is_resize_needed = true;
    };

    if (is_resize_needed)
        serialized_buffer->buffer = realloc(serialized_buffer->buffer, serialized_buffer->size);
}

void serialize_data(serialized_buffer_t *serialized_buffer, void *data, int type_size)
{
    // Will resize the buffer if needed
    resize_buffer(serialized_buffer, type_size);

    // Just copy the data into buffer
    memcpy((void *)serialized_buffer->buffer + serialized_buffer->seek_index, data, type_size);
    serialized_buffer->seek_index += type_size;
}

void unserialize_data(void *destination, serialized_buffer_t *serialize_buffer, int type_size)
{
    // TODO check params
    int available_space = serialize_buffer->size - serialize_buffer->seek_index;

    if (available_space < type_size)
        return;

    memcpy(destination, serialize_buffer->buffer + serialize_buffer->seek_index, type_size);
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
