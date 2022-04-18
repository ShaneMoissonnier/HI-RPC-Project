#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "client.h"
#include <ctype.h>
#include <stdbool.h>
#define MAX_ELT 20
#define MAX_ELTSIZE 10


int main()
{
    struct sockaddr_in serverAddr;
    int socketFd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serverAddr, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(22000);

    bool initialization;
    if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &initialization, sizeof(int)) == -1)
    {
        printf("Error during socket configuration!\n");
        return -1;
    }

    // Set server address to localhost "127.0.0.1"
    inet_pton(AF_INET, "127.0.0.1", &(serverAddr.sin_addr));

    // Connect to the server
    connect(socketFd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in));

    Request req = {
        .ack = ACK,
        .id = 0,
    };

    Response res = {0};

    while (true)
    {
        // parse_input(expression, &req);
        printRequest(req);

        // Send a request to the server
        (void)(write(socketFd, (char *)&req, sizeof(Request)));

        // Read server's response
        (void)(read(socketFd, (char *)&res, sizeof(Response)));

        printResponse(res);
        bzero(&res, sizeof(Response));


        getchar();
    }

    close(socketFd);

    return 0;
}

