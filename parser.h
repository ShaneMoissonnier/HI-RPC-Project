#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "common.h"

#define MAX_STRUCT_SIZE 4096
#define MAX_WORD_SIZE 4096

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

typedef struct message_list
{
    message_t head;
    message_t tail;
} * message_list_t;

typedef struct service
{
    char name[MAX_WORD_SIZE];

    char param[MAX_WORD_SIZE];
    char reply[MAX_WORD_SIZE];

    struct service *next;
} * service_t;

typedef struct service_list
{
    service_t head;
    service_t tail;
} * service_list_t;

typedef struct parser_result
{
    message_list_t message_list;
    service_list_t service_list;
} * parser_result_t;

typedef struct math_operation
{
    int operation;
    int operandA;
    int operandB;
} * math_operation_t;

void replace_in_string(char *string, char *word_to_replace, char *word);

char *enum_variable_type_to_string(int variable_type);

bool compare_words(char *first_word, char *second_word);

int read_word(FILE *specification_file, char *word);

int write_word(FILE *specification_file, char *word);

bool read_word_and_compare(FILE *specification_file, char *word_to_compare);

bool parse_name(FILE *specification_file, char *word);

bool parse_name_and_copy(FILE *specification_file, char *word, char *destination);

message_list_t init_message_list();

void add_message_to_list(message_t new_message, message_list_t message_list);

bool parse_params(FILE *specification_file, message_t message, char *word);

bool parse_message(FILE *specification_file, message_list_t message_list);

service_list_t init_service_list();

void add_service_to_list(service_t new_service, service_list_t service_list);

bool parse_service(FILE *specification_file, service_list_t service_list);

bool parse_file(FILE *specification_file, parser_result_t result);

void free_parser_result(parser_result_t parser_result);

math_operation_t parse_input(char *input);

#endif