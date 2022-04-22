#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parser.h"

void generate_client_stub(parser_result_t parser_result);
void generate_server_stub(parser_result_t parser_result);

#endif