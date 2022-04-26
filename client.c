#include "client.h"
#include "parser.h"

Request_t convert_math_to_request(math_operation_t math_operation)
{
    if (math_operation == NULL)
        return NULL;

    Request_t req = malloc(sizeof(struct Request));
    req->operandB = math_operation->operandB;
    req->operandA = math_operation->operandA;
    req->operation = math_operation->operation;

    return req;
}

int main()
{
    client_t client = create_client("127.0.0.1", 22000);

    if (client == NULL)
    {
        printf("Unable to connect client!\n");
        return -1;
    }

    Response_t resp = (Response_t)malloc(sizeof(Response_t));

    char *expression = malloc(sizeof(char) * 20);

    printf("If you want to exit, enter 'exit'\n");

    while (true)
    {
        printf("Enter an expression (ex: 2+2): ");
        scanf("%s", expression);

        if (strcmp(expression, "exit") == 0)
            break;

        math_operation_t math_operation = parse_input(expression);
        Request_t req = convert_math_to_request(math_operation);

        if (req == NULL)
        {
            printf("unknown operation !\n");
            continue;
        }

        printf("Send operation : %d %d %d\n", req->operandA, req->operation, req->operandB);
        rpc_send(client, req, resp);
        printf("Server's response : %d\n", resp->result);

        free(req);
        getchar();
    }

    free(resp);
    close_client(client);
    return 0;
}
