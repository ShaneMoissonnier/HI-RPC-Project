#include "parser.h"

void replace_word_in_file(FILE *template_file, char *word_to_replace, char *word)
{
    // TODO
}

bool compare_words(char *first_word, char *second_word)
{
    return strcmp(first_word, second_word) == 0;
}

int read_word(FILE *specification_file, char *word)
{
    return fscanf(specification_file, " %512s", word);
}

bool read_word_and_compare(FILE *specification_file, char *word_to_compare)
{
    char word[MAX_WORD_SIZE];

    int result = read_word(specification_file, word);

    if (!result)
        return false;

    return compare_words(word, word_to_compare);
}

bool parse_name(FILE *specification_file, char *word)
{
    // Read name
    bool result_name = read_word(specification_file, word);

    if (!result_name)
        return false;

    return true;
}

bool parse_name_and_copy(FILE *specification_file, char *word, char *destination)
{
    int result_name = parse_name(specification_file, word);

    if (!result_name)
        return false;

    strcpy(destination, word);

    return true;
}

message_list_t init_message_list()
{
    message_list_t message_list = (message_list_t)malloc(sizeof(struct message_list));

    message_t message_dummy = (message_t)malloc(sizeof(struct message));
    message_dummy->params = NULL;

    message_list->head = message_dummy;
    message_list->tail = message_dummy;

    return message_list;
}

void add_message_to_list(message_t new_message, message_list_t message_list)
{
    message_list->tail->next = new_message;
    message_list->tail = new_message;
}

bool parse_params(FILE *specification_file, message_t message, char *word)
{
    message_params_t params;

    message->params = (message_params_t)malloc(sizeof(struct message_params));
    params = message->params;

    bool is_param_valid = true;

    if (compare_words(word, "int"))
    {
        params->type = INT;
    }
    else if (compare_words(word, "double"))
    {
        params->type = DOUBLE;
    }
    else
    {
        printf("Unknow type!\n");
        is_param_valid = false;
    }

    if (!is_param_valid)
        goto PARAMS_PARSING_ERROR;

    if (!parse_name(specification_file, word))
        goto PARAMS_PARSING_ERROR;

    strcpy(params->name, word);

    // add param to message params list
    message_params_t next_params = message->params;
    message->params = params;
    params->next = next_params;

    return true;

PARAMS_PARSING_ERROR:
    free(params);
    return false;
}

bool parse_message(FILE *specification_file, message_list_t message_list)
{
    message_t new_message = (message_t)malloc(sizeof(struct message));
    char word[MAX_WORD_SIZE];

    int params_count = 0;

    if (!parse_name(specification_file, word))
        goto MESSAGE_PARSING_ERROR;

    strcpy(new_message->name, word);

    printf("Message name : %s\n", word);

    if (!read_word_and_compare(specification_file, "{"))
        goto MESSAGE_PARSING_ERROR;

    bool params_valids = true;

    while (read_word(specification_file, word) && !compare_words(word, "}"))
    {
        params_valids = parse_params(specification_file, new_message, word);

        if (!params_valids)
            break;

        params_count++;
    }

    if (!params_valids || params_count == 0)
        goto MESSAGE_PARSING_ERROR;

    if (!compare_words(word, "}"))
        goto MESSAGE_PARSING_ERROR;

    add_message_to_list(new_message, message_list);

    return true;

MESSAGE_PARSING_ERROR:
    free(new_message);
    return false;
}

service_list_t init_service_list()
{
    service_list_t service_list = (service_list_t)malloc(sizeof(struct service_list));

    service_t service_dummy = (service_t)malloc(sizeof(struct service));

    service_list->head = service_dummy;
    service_list->tail = service_dummy;

    return service_list;
}

void add_service_to_list(service_t new_service, service_list_t service_list)
{
    service_list->tail->next = new_service;
    service_list->tail = new_service;
}

bool parse_service(FILE *specification_file, service_list_t service_list)
{
    service_t new_service = (service_t)malloc(sizeof(struct service));
    char word[MAX_WORD_SIZE];

    if (!parse_name_and_copy(specification_file, word, new_service->name))
        goto SERVICE_PARSING_ERROR;

    printf("Service name : %s\n", word);

    if (!read_word_and_compare(specification_file, "{"))
        goto SERVICE_PARSING_ERROR;

    if (!read_word_and_compare(specification_file, "param"))
        goto SERVICE_PARSING_ERROR;

    if (!parse_name_and_copy(specification_file, word, new_service->param))
        goto SERVICE_PARSING_ERROR;

    if (!read_word_and_compare(specification_file, "reply"))
        goto SERVICE_PARSING_ERROR;

    if (!parse_name_and_copy(specification_file, word, new_service->reply))
        goto SERVICE_PARSING_ERROR;

    if (!read_word_and_compare(specification_file, "}"))
        goto SERVICE_PARSING_ERROR;

    add_service_to_list(new_service, service_list);

    return true;

SERVICE_PARSING_ERROR:
    free(new_service);
    return false;
}

bool parse_file(FILE *specification_file, parser_result_t result)
{
    char word[MAX_WORD_SIZE];

    bool parsing_result = true;

    message_list_t message_list = init_message_list();

    service_list_t service_list = init_service_list();

    while (read_word(specification_file, word) != EOF && parsing_result)
    {
        // TODO: need refactoring
        if (compare_words(word, "message"))
        {
            parsing_result = parse_message(specification_file, message_list);
        }
        else if (compare_words(word, "service"))
        {
            parsing_result = parse_service(specification_file, service_list);
        }
    }

    result->message_list = message_list;
    result->service_list = service_list;

    return parsing_result;
}

void free_parser_result(parser_result_t parser_result)
{
    message_t current_message = parser_result->message_list->head;
    service_t current_service = parser_result->service_list->head;

    while(current_message != NULL)
    {
        message_t next_message = current_message->next;
        free(current_message);
        current_message = next_message;
    }
    
    while(current_service != NULL)
    {
        service_t next_service = current_service->next;
        free(current_service);
        current_service = next_service;
    }

    free(parser_result);
}