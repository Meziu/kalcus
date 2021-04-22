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


typedef struct
{
    void** array;
    int length;
} array;

void free_array(array arr, bool free_items);
void remove_at(array* arr, int index);


typedef struct Node Node;

struct Node
{
    Node* left_child;
    Node* right_child;

    bool is_operation;
    float value;
};

void resolve_node(Node* node);
void free_nodes(Node** node);
Node* node_tree_from_array(array* raw_nodes);
