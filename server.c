#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "server.h"

int processAddition(const Request *request, Response *response)
{
  int operandA = request->params[0];
  int operandB = request->params[1];
  
  response->data = operandA + operandB;
  printf("ADD = %d + %d\n", operandA, operandB);
  return true;
}

int processSubstraction(const Request *request, Response *response)
{
  int operandA = request->params[0];
  int operandB = request->params[1];
  
  response->data = operandA - operandB;
  printf("SUB = %d - %d\n", operandA, operandB);
  return true;
}

int processMultiplication(const Request *request, Response *response)
{
  int operandA = request->params[0];
  int operandB = request->params[1];
  
  response->data = operandA * operandB;
  printf("MUL = %d * %d\n", operandA, operandB);
  return true;
}

int processDivision(const Request *request, Response *response)
{
  int operandA = request->params[0];
  int operandB = request->params[1];
  
  response->data = operandA / operandB;
  printf("DIV = %d / %d\n", operandA, operandB);

  return true;
}

int requestProcessing(const Request *request, Response *response)
{
  switch (request->op)
  {
  case ADD:
    return processAddition(request, response);
  case SUB:
    return processSubstraction(request, response);
  case MUL:
    return processMultiplication(request, response);
  case DIV:
    return processDivision(request, response);
  default:
    return false;
  }
}

int main()
{
  struct sockaddr_in serverAddr;
  int listenSocketFd = socket(AF_INET, SOCK_STREAM, 0);

  bool initialization;
  if (setsockopt(listenSocketFd, SOL_SOCKET, SO_REUSEADDR, &initialization, sizeof(int)) == -1)
  {
    printf("Error during socket configuration!\n");
    return -1;
  }

  bzero(&serverAddr, sizeof(serverAddr));

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htons(INADDR_ANY);
  serverAddr.sin_port = htons(22000);

  bind(listenSocketFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

  listen(listenSocketFd, 1);

  // Wait for client connection request
  int clientSocket = accept(listenSocketFd, (struct sockaddr *)NULL, NULL);

  Request req = {0};
  Response res = {0};

  size_t n = 0;

  while ((n = read(clientSocket, &req, sizeof(req))) >= 0) {

    printf("Bytes readed : %ld\n", n);

    if (req.ack != ACK) {
      printf("ACK Problem (%d)\n", req.ack);
      continue;
    }

    printRequest(req);

    res.ack = req.ack;
    res.id = req.id;
    res.status = (bool)requestProcessing(&req, &res);

    printResponse(res);

    (void)(write(clientSocket, (char *)&res, sizeof(Response)));

    bzero(&req, sizeof(Request));
    bzero(&res, sizeof(Response));
  }

  close(clientSocket);

  return 0;
}
