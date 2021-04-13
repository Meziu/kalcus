#pragma once

#include <string.h>
#include "nodes.h"

#define is_number(x) (((int)(x) < 57) && ((int)(x) > 48))

void clean_input(char** end_str, char* inputs[], int n);
int parse_and_node(const char* input, int input_length);