#include "generator.h"

void generate_struct_message_params(message_params_t params, char *params_string)
{
    message_params_t current_param = params;

    while (current_param != NULL)
    {
        int variable_type = current_param->type;
        char *variable_name = current_param->name;

        char buffer[MAX_WORD_SIZE];
        snprintf(buffer, MAX_WORD_SIZE, "\t%s %s;\n", enum_variable_type_to_string(variable_type), variable_name);

        strcat(params_string, buffer);

        current_param = current_param->next;
    }
}

char *generate_struct(parser_result_t parser_result)
{
    message_t current_message = parser_result->message_list->head;

    char *struct_string_list = (char *)malloc(MAX_STRUCT_SIZE);
    bzero(struct_string_list, MAX_STRUCT_SIZE);

    while (current_message != NULL)
    {
        if (compare_words(current_message->name, ""))
        {
            current_message = current_message->next;
            continue;
        }

        char struct_string[MAX_WORD_SIZE];

        char params_string[MAX_WORD_SIZE];
        bzero(params_string, MAX_WORD_SIZE);

        generate_struct_message_params(current_message->params, params_string);

        char *variable_name = current_message->name;
        char *params_string_list = params_string;

        // For now packed attribute is needed because serialization is not used 
        // source : https://stackoverflow.com/a/13119155
        // TODO: use serialization
        snprintf(struct_string, MAX_WORD_SIZE, "typedef struct %s \n{\n%s\n} __attribute__((packed)) *%s_t;\n\n", variable_name, params_string_list, variable_name);

        strcat(struct_string_list, struct_string);

        current_message = current_message->next;
    }

    return struct_string_list;
}

void generate_client_stub(parser_result_t parser_result)
{
    FILE *client_stub_file = fopen("client_stub.h", "w");
    FILE *template_file = fopen("client_template.template", "r");

    char readed_line[MAX_WORD_SIZE];
    char *struct_string = generate_struct(parser_result);

    service_t service = parser_result->service_list->head->next;

    // Just to be safe
    if (service == NULL)
    {
        printf("Cannot generate client stub!\n");
        return;
    }

    rewind(template_file);
    while (!feof(template_file))
    {
        bzero(readed_line, MAX_WORD_SIZE);

        fgets(readed_line, MAX_WORD_SIZE, template_file);

        replace_in_string(readed_line, "[struct_header]", struct_string);

        replace_in_string(readed_line, "[struct_param]", service->param);

        replace_in_string(readed_line, "[struct_reply]", service->reply);

        write_word(client_stub_file, readed_line);
    }

    free(struct_string);

    fclose(client_stub_file);
    fclose(template_file);
    return;
}

void generate_server_stub(parser_result_t parser_result)
{
    FILE *server_stub_file = fopen("server_stub.h", "w");
    FILE *template_file = fopen("server_template.template", "r");

    char readed_line[MAX_WORD_SIZE];
    char *struct_string = generate_struct(parser_result);

    service_t service = parser_result->service_list->head->next;

    // Just to be safe
    if (service == NULL)
    {
        printf("Cannot generate server stub!\n");
        return;
    }

    rewind(template_file);
    while (!feof(template_file))
    {
        bzero(readed_line, MAX_WORD_SIZE);

        fgets(readed_line, MAX_WORD_SIZE, template_file);

        replace_in_string(readed_line, "[struct_header]", struct_string);

        replace_in_string(readed_line, "[struct_param]", service->param);

        replace_in_string(readed_line, "[struct_reply]", service->reply);

        write_word(server_stub_file, readed_line);
    }

    free(struct_string);

    fclose(server_stub_file);
    fclose(template_file);
    return;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage : ./generator <idl-spectification-file>\n");
        return -1;
    }

    FILE *specification_file = fopen(argv[1], "r");

    if (specification_file == NULL)
    {
        printf("Specification file not found !\n");
        return -2;
    }

    parser_result_t parser_result;
    parser_result = (parser_result_t)malloc(sizeof(struct parser_result));

    bool parsing_result = parse_file(specification_file, parser_result);

    fclose(specification_file);

    if (!parsing_result)
    {
        printf("Unable to parse specification file\n");
        return -3;
    }

    generate_client_stub(parser_result);
    generate_server_stub(parser_result);

    free_parser_result(parser_result);
    return 0;
}