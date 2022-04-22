#include "generator.h"

void generate_client_stub(parser_result_t parser_result)
{
    FILE *client_stub_file = fopen("client_stub.h", "w");

    message_t current_message = parser_result->message_list->head;

    while (current_message != NULL)
    {
        if (compare_words(current_message->name, ""))
        {
            current_message = current_message->next;
            continue;
        }

        current_message = current_message->next;
    }

    fclose(client_stub_file);
    return;
}

void generate_server_stub(parser_result_t parser_result)
{
    FILE *server_stub_file = fopen("server_stub.h", "w");

    service_t current_service = parser_result->service_list->head;

    while (current_service != NULL)
    {
        if (compare_words(current_service->name, ""))
        {
            current_service = current_service->next;
            continue;
        }

        current_service = current_service->next;
    }
    fclose(server_stub_file);
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