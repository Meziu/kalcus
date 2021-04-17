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

void _get_node_operands(array* nodes_array, int index)
{
    Node* left_node  = ((Node*)(nodes_array->array[index-1]));
    Node* right_node = ((Node*)(nodes_array->array[index+1]));

    // if there is an invalid operation before or after the node call the input error
    if (right_node->is_operation && (right_node->left_child == NULL || right_node->right_child == NULL)) e_call_error(ERR_INVALID_INPUT);
    if (left_node->is_operation  && (left_node->left_child  == NULL || left_node->right_child  == NULL)) e_call_error(ERR_INVALID_INPUT);

    Node* current_node = ((Node*)(nodes_array->array[index]));
    current_node->left_child = left_node;
    current_node->right_child = right_node;

    remove_at(nodes_array, index-1);
    remove_at(nodes_array, index);
}

Node* node_tree_from_array(array* raw_nodes)
{
    for (int i=0; i<raw_nodes->length; i+=1)
    {
        Node* current_node = ((Node*)(raw_nodes->array[i]));

        if (current_node->is_operation)
        {
            if (current_node->value == OP_MULT || current_node->value == OP_DIV || current_node->value == OP_POW)
            {
                _get_node_operands(raw_nodes, i);
                i-=1;
            }
        }
    }
    for (int i=0; i<raw_nodes->length; i+=1)
    {
        Node* current_node = ((Node*)(raw_nodes->array[i]));

        if (current_node->is_operation)
        {
            if (current_node->value == OP_SUM || current_node->value == OP_SUB)
            {
                _get_node_operands(raw_nodes, i);
                i-=1;
            }
        }
    }
    return raw_nodes->array[0];
}



void free_array(array arr)
{
    for (int i=0; i<arr.length; i+=1)
    {
        free(arr.array[i]);
    }
    free(arr.array);
}

void remove_at(array* arr, int index)
{
    if (index > arr->length || arr->array == NULL)
    {
        printf("dude tf");
        return;
    }
    
    void** new_array = malloc(sizeof(void*)*(arr->length-1));

    int t_in = 0;
    for (int i=0; i<arr->length; i+=1)
    {
        if (i == index)
            continue;
        
        new_array[t_in] = arr->array[i];
        t_in += 1;
    }

    free(arr->array);
    arr->array = new_array;
    arr->length -= 1;
}
