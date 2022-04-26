#include "client.h"
#include "parser.h"

Request_t convertStruct(math_operation_t math_operation)
{
    Request_t req=malloc(sizeof(struct Request));
    req->operandB=math_operation->operandB;
	req->operandA=math_operation->operandA;
	req->operation=math_operation->operation;
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
    Request_t req = (Request_t) malloc(sizeof(Request_t));
    Response_t resp = (Response_t)malloc(sizeof(Response_t));

    // req->operation = 2;
    // req->operandA = 10;
    // req->operandB = 27;
    char* expression=malloc(sizeof(char)*20);
    // TODO: replace while condition to close connection
    printf("If you want to exit, enter 'exit'\n");
    
    while(true)
    {
        bzero(req, sizeof(struct Request));

        
        printf("Enter an expression (ex: 2+2): ");
        scanf("%s", expression);
        if (strcmp(expression, "exit") == 0)
        {
            break;
        }        
        math_operation_t math_operation = parse_input(expression);
        req = convertStruct(math_operation);
        
        printf("Send operation : %d %d %d\n", req->operandA, req->operation, req->operandB);
        rpc_send(client, req, resp);
        printf("Server's response : %d\n", resp->result);

        getchar();
    }

    free(req);
    free(resp);
    close_client(client);
    return 0;
}

