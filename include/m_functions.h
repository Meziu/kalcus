#pragma once

#include <math.h>
#include "e_errors.h"

float m_mult (float x, float y);
float m_div  (float x, float y);
float m_sum  (float x, float y);
float m_sub  (float x, float y);
float m_power(float x, float y);

float stringToFloat(char* string);

//unused
float m_sqrt (float x);
