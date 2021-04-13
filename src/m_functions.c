#include "m_functions.h"

float m_mult(float x, float y)
{
    return x*y;
}

float m_div(float x, float y)
{
    if(y == 0)
        e_call_error(ERR_DIV_BY_ZERO);
    return x/y;
}

float m_sum(float x, float y)
{
    return x+y;
}

float m_sub(float x, float y)
{
    return x-y;
}

float m_power(float x, float y)
{
    return (float)pow(x, y);
}

float m_sqrt(float x)
{
    if (x < 0)
        e_call_error(ERR_NEG_SQRT);
    return (float)sqrt(x);
}


float stringToFloat(char *string)
{
    float result= 0.0;
    int len = strlen(string);
    int dotPosition = 0;

    for (int i = 0; i < len; i++)
    {
        if (string[i] == '.')
        {
          dotPosition = len - i  - 1;
        }
        else
        {
          result = result * 10.0 + (string[i]-'0');
        }
      }

      while (dotPosition--)
      {
        result /= 10.0;
      }

    return result;
}
