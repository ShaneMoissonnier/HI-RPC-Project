#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "client.h"


//method parsing the input an expression mathematic from the user
int parse_input(char *input, char *op1, char *op2, char *op)
{
    int i = 0;
    while(input[i] != '\0')
    {
        if(input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
        {
            *op = input[i];
            break;
        }
        i++;
    }
    if(i == 0)
    {
        return -1;
    }
    int j = 0;
    while(input[i] != '\0')
    {
        if(input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
        {
            break;
        }
        op1[j] = input[i];
        i++;
        j++;
    }
    op1[j] = '\0';
    j = 0;
    i++;
    while(input[i] != '\0')
    {
        op2[j] = input[i];
        i++;
        j++;
    }
    op2[j] = '\0';
    return 0;
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
      .op = MUL,
      .params = {8, 2}
  };

  Response res = {0};

  while (true) {
    printRequest(req);

    // Send a request to the server
    (void)(write(socketFd, (char *)&req, sizeof(Request)));

    // Read server's response
    (void)(read(socketFd, (char *)&res, sizeof(Response)));

    printResponse(res);

    bzero(&res, sizeof(Response));

    // TODO replace with parsing  : faire l'appel a la fonction parse_input
    char op1[10];
    char op2[10];
    char op;
    printf("Enter an expression (ex: 2+2): ");
    scanf("%s", op1);
    parse_input(op1, op1, op2, &op); 
    getchar();
  }

  close(socketFd);

  return 0;
}
