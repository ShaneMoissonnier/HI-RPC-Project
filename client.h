#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "common.h"
int find_math_operation(char *op);
void parse_input(char *input,Request* req);
void infix_to_postfix(char *infix,char *postfix);
void evalPostfix(char**);
#endif