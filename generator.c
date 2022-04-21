#include "generator.h"

void generate_client_stub()
{
    FILE *client_stub_file = fopen("client_stub.h", "w");

    fclose(client_stub_file);
    return;
}

void generate_server_stub()
{
    FILE *server_stub_file = fopen("server_stub.h", "w");

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

    bool parsing_result = parse_file(specification_file);

    fclose(specification_file);

    if (!parsing_result)
    {
        printf("Unable to parse specification file\n");
        return -3;
    }

    generate_client_stub();
    generate_server_stub();

    return 0;
}