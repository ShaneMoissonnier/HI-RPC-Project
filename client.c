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




// method parsing the input an expression mathematic from the user : 2+2
void parse_input(char *input, Request *req)
{
    
    char* tmp=input;
    char op;
    char op1[10];
    char op2[10];
    int i=0;
    size_t input_size=strlen(input);
    //getting the first operand
    while((i<input_size)&&(isdigit(tmp[i])!= 0)){
        op1[i]=tmp[i];
        i++;
    }
    //getting the operator
    op=tmp[i++];
    int j=0;
    //getting the second operand
    while((i<input_size)&&(isdigit(tmp[i])!= 0)){
        op2[j++]=tmp[i++];
    }

    //setting the request 
    int ope1=atoi(op1);
    int ope2=atoi(op2);
    req->params[0]=ope1;
    req->params[1]=ope2;
    if(op == '+'){
        req->op=ADD;
    }
    else if(op == '-'){
        req->op=SUB;
    }
    else if(op == '*'){
        req->op=MUL;
    }
    else if(op == '/'){
        req->op=DIV;
    }
    else{
        printf("Invalid operation\n");
        return;
    }

}

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
        // TODO replace with parsing  : faire l'appel a la fonction parse_input
        char expression[10];
        printf("Enter an expression (ex: 2+2): ");
        scanf("%s", expression);
        parse_input(expression, &req);
        printRequest(req);

        // Send a request to the server
        (void)(write(socketFd, (char *)&req, sizeof(Request)));

        // Read server's response
        (void)(read(socketFd, (char *)&res, sizeof(Response)));

        printResponse(res);
        bzero(&res, sizeof(Response));


        // getchar();
    }

    close(socketFd);

    return 0;
}

3 + 2 * 6
3 