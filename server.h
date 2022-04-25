#ifndef _SERVER_H_
#define _SERVER_H_

#include "common.h"
#include "server_stub.h"
#include <math.h>

int processAddition(const Request_t request, Response_t response);

int processSubstraction(const Request_t request, Response_t response);

int processMultiplication(const Request_t request, Response_t response);

int processDivision(const Request_t request, Response_t response);

int processPow(const Request_t request, Response_t response);

Response_t requestProcessing(Request_t request);

#endif