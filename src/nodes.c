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