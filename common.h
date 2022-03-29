#ifndef COMMON_H
#define COMMON_H

#define ACK 0xA

typedef enum
{
  ADD = 0,
  SUB,
  MUL,
  DIV
} OpType;

typedef struct
{
  char ack;
  char id;
  OpType op;
  char params[2];
} Request;

typedef struct
{
  char ack;
  char id;
  char status;
  char data;
} Response;

void printRequest(Request request)
{
  printf("Request: ACK: %d, ID: %d, OP: %d, PARAMS: [%d, %d]\n",
         request.ack,
         request.id,
         request.op,
         request.params[0],
         request.params[1]);
}

void printResponse(Response response)
{
  printf("Response: ACK: %d, ID: %d, STATUS: %d, DATA: %d\n",
         response.ack,
         response.id,
         response.status,
         response.data);
}

#endif
