#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "client.h"
#include "serialization.h"

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

    req->op = 0;
    req->operandA = 10;
    req->operandB = 2;

    rpc_send(client, req, resp);

    printf("Server's response : %d\n", resp->result);

    free(req);
    free(resp);
    close_client(client);
    return 0;
}

