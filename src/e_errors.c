#include "e_errors.h"

void e_call_error(int err_code)
{
    switch (err_code)
    {
    case ERR_NEG_SQRT:
        error_print(ERR_NEG_SQRT_TXT);
        break;
    case ERR_DIV_BY_ZERO:
        error_print(ERR_DIV_BY_ZERO_TXT);
        break;
    case ERR_NO_MATH:
        error_print(ERR_NO_MATH_TXT);
        break;
    case ERR_NO_INPUT:
        error_print(ERR_NO_INPUT_TXT);
        break;
    case ERR_INVALID_INPUT:
        error_print(ERR_INVALID_INPUT_TXT);
        break;
    }
    exit(1);
}