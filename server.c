#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "server.h"
#include "serialization.h"

int processAddition(const Request_t request, Response_t response)
{
  int operandA = request->operandA;
  int operandB = request->operandB;
  
  response->result = operandA + operandB;
  printf("ADD = %d + %d\n", operandA, operandB);
  return true;
}

int processSubstraction(const Request_t request, Response_t response)
{
  int operandA = request->operandA;
  int operandB = request->operandB;
  
  response->result = operandA - operandB;
  printf("SUB = %d - %d\n", operandA, operandB);
  return true;
}

int processMultiplication(const Request_t request, Response_t response)
{
  int operandA = request->operandA;
  int operandB = request->operandB;
  
  response->result = operandA * operandB;
  printf("MUL = %d * %d\n", operandA, operandB);
  return true;
}

int processPow(const Request_t request, Response_t response)
{
  //on doit pouvoir diminuer sa compléxité
  int operandA = request->operandA;
  int operandB = request->operandB;

  response->result = pow(operandA, operandB);
  printf("POW = %d ^ %d\n", operandA, operandB);
  return true;
}

int processDivision(const Request_t request, Response_t response)
{
  int operandA = request->operandA;
  int operandB = request->operandB;
  
  response->result = operandA / operandB;
  printf("DIV = %d / %d\n", operandA, operandB);

  return true;
}

Response_t requestProcessing(Request_t request)
{
  Response_t response = (Response_t) malloc(sizeof(Response_t));

  switch (request->op)
  {
  case ADD:
    processAddition(request, response);
    break;
  case SUB:
    processSubstraction(request, response);
    break;
  case MUL:
    processMultiplication(request, response);
    break;
  case DIV:
    processDivision(request, response);
    break;
  case POW:
    processPow(request, response);
    break;
  default:
    break;
  }
  return response;
}

int main()
{
  server_t server = create_server(22000);

  start_server(server, requestProcessing);
  return 0;
}
