#pragma once

#include <stdlib.h>
#include "m_functions.h"
#include <stdbool.h>

enum
{
    OP_SUM,
    OP_SUB,
    OP_MULT,
    OP_DIV,
    OP_POW
};

extern float (*operations[])(float, float);

typedef struct Node Node;

struct Node
{
    Node* left_child;
    Node* right_child;

    bool is_operation;
    float value;
};

void resolve_node(Node* node);