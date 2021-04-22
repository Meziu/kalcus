#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define error_print(txt) printf("ERROR OCCURED: %s\n", txt)

enum
{
    ERR_NO_MATH,
    ERR_DIV_BY_ZERO,
    ERR_NEG_SQRT,
    ERR_NO_INPUT,
    ERR_INVALID_INPUT,
    ERR_NON_MATCHING_BRACKETS
};

#define ERR_NEG_SQRT_TXT                "EVEN ROOT OF NEGATIVE NUMBER"
#define ERR_DIV_BY_ZERO_TXT             "DIVISION BY ZERO"
#define ERR_NO_MATH_TXT                 "NO SUPPORTED MATHEMATICAL EXPRESSION FOUND"
#define ERR_NO_INPUT_TXT                "NO INPUT SPECIFIED, RETRY WITH INPUT"
#define ERR_INVALID_INPUT_TXT           "INPUT INVALID, CHECK THE SYMBOLS AND SYNTAX"
#define ERR_NON_MATCHING_BRACKETS_TXT   "BRACKET DOESN'T MATCH ANY OTHER ONE"


void e_call_error(int err_code);
