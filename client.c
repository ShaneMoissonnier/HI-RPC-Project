#include "client.h"

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

    req->operation = 2;
    req->operandA = 10;
    req->operandB = 27;

    // TODO: replace while condition to close connection
    while(true)
    {
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

