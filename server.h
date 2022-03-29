#ifndef _SERVER_H_
#define _SERVER_H_

#include "common.h"

int processAddition(const Request *request, Response *response);

int processSubstraction(const Request *request, Response *response);

int processMultiplication(const Request *request, Response *response);

int processDivision(const Request *request, Response *response);

int requestProcessing(const Request *request, Response *response);

#endif