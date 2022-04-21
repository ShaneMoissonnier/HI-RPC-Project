#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_WORD_SIZE 512

typedef struct message_params
{
    enum
    {
        INT,
        DOUBLE
    } type;

    char name[MAX_WORD_SIZE];

    struct message_params *next;
} * message_params_t;

typedef struct message
{
    char name[MAX_WORD_SIZE];
    message_params_t params;

    struct message *next;
} * message_t;

typedef struct service
{
    char name[MAX_WORD_SIZE];

    char param[MAX_WORD_SIZE];
    char reply[MAX_WORD_SIZE];

    struct service *next;
} * service_t;

bool compare_words(char *first_word, char *second_word);

int read_word(FILE *specification_file, char *word);

bool read_word_and_compare(FILE *specification_file, char *word_to_compare);

bool parse_name(FILE *specification_file, char *word);

bool parse_name_and_copy(FILE *specification_file, char *word, char *destination);

void add_message_to_list(message_t new_message, message_t message_list);

bool parse_params(FILE *specification_file, message_t message, char *word);

bool parse_message(FILE *specification_file, message_t message_list);

bool parse_service(FILE *specification_file, service_t service_list);

bool parse_file(FILE *specification_file);

#endif