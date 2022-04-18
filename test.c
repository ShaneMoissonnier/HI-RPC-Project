#include <stdio.h>
#include <stdlib.h>
#include "serialization.h"

int main(int argc, char *argv[])
{
    serialized_buffer_t *s_buffer = init_buffer();

    int number = 10;
    char *test_string = "test";

    serialize_data(s_buffer, &number, sizeof(int));
    serialize_data(s_buffer, test_string, strlen(test_string) + 1);

    // Don't forget to reset seek index before unserialize
    reset_seek(s_buffer);

    int number_unserial = 0;
    char *string_test = (char *)malloc(strlen(test_string) + 1);

    unserialize_data(&number_unserial, s_buffer, sizeof(int));
    unserialize_data(string_test, s_buffer, strlen(test_string) + 1);

    printf("%d %s\n", number_unserial, string_test);

    free_buffer(s_buffer);
    return 0;
}