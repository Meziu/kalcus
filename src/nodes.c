#include "nodes.h"

float (*operations[])(float, float) = {
    m_sum,
    m_sub,
    m_mult,
    m_div,
    m_power
};

void resolve_node(Node* node)
{
    if (node->is_operation)
    {
        resolve_node(node->left_child);
        resolve_node(node->right_child);

        node->value = operations[(int)(node->value)](node->left_child->value, node->right_child->value);
        node->is_operation = false;
    }
}

void free_nodes(Node* node)
{
    if (node->left_child != NULL)
        free_nodes(node->left_child);

    if (node->right_child != NULL)
        free_nodes(node->right_child);

    free(node);
}
