#include "p_parser.h"

char* all_symbols       = "*/^+-.()";
char* operation_symbols = "*/^+-()";

int chars_in_string(const char* string, char* chars_array, int array_len, int start_from)
{
    for (int i=start_from; i<strlen(string); i+=1)
    {
        for (int c=0; c<array_len; c+=1)
        {
            if (string[i] == chars_array[c])
            {
                return i;
            }
        }
    }
    return -1;
}

// remove occurrences of a certain char in a string
void remove_all_char(char* str, char c) {
    char *pr = str;
    char *pw = str;

    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}

bool check_valid_characters(char* str)
{
    // if first or last 
    if ((!is_number(str[0]) && str[0]!='(') || (!is_number(str[strlen(str)-1]) && str[strlen(str)-1]!=')'))
        e_call_error(ERR_INVALID_INPUT);

    if (chars_in_string(str, all_symbols, strlen(all_symbols), 0)==-1)
        e_call_error(ERR_NO_MATH);

    // there is at least 1 number
    bool numbers_present = false;
    
    // check string for invalid symbols
    for (int i=0; i<strlen(str); i+=1)
    {
        // if current char isn't a number (ASCII stuff)
        if (!is_number(str[i]))
        {
            bool symbol_valid = false;
            for (int c=0; c<strlen(all_symbols); c+=1)
            {
                // if symbol is valid
                if (str[i] == all_symbols[c])
                    symbol_valid = true;
            }
            if (!symbol_valid)
                e_call_error(ERR_INVALID_INPUT);
        }
        else
        {
            numbers_present = true;
        }
    }
    // if there aren't any numbers
    if (!numbers_present)
        e_call_error(ERR_NO_MATH);
}

void clean_input(char** end_str, char* inputs[], int n)
{
    if (n<2)
        e_call_error(ERR_NO_INPUT);
    // string must be initialized to use strcat
    *end_str = inputs[1];
    
    // get 1 big string
    for (int i=2; i < n; i+=1)
    {
        *end_str = strcat(*end_str, inputs[i]);
    }

    // remove any spaces to reduce input
    remove_all_char(*end_str, ' ');


    // control if now the string is ok, otherwise throw a tantrum
    check_valid_characters(*end_str);
}


array parse_input(char* input)
{
    const int input_len = strlen(input);

    char** temp_output     = malloc(input_len*8);
    char*  temp_out_string = malloc(1);

    int current_search  = strcspn(input, operation_symbols);
    int search_stack    = 0;
    int output_array_length = 0;

    char* temp_input = input;

    while (input_len > search_stack)
    {
        if (current_search == 0)
            current_search = 1;

        temp_out_string = realloc(temp_out_string, current_search+1);
        memset(temp_out_string, 0, current_search+1);
        memcpy(temp_out_string, temp_input, current_search);

        temp_output[output_array_length] = malloc(current_search+1);
        memcpy(temp_output[output_array_length], temp_out_string, current_search+1);

        output_array_length += 1;
        search_stack        += current_search;
        temp_input           = input + search_stack;

        current_search = strcspn(temp_input, operation_symbols);
    }

    char** output = malloc(output_array_length*8);
    memcpy(output, temp_output, output_array_length*8);


    free(temp_output);
    free(temp_out_string);
    return (array){(void**)output, output_array_length};
}

array make_nodes_array(array* input_array)
{
    array temp_output = {malloc(8*input_array->length), input_array->length};

    int i;
    for (i=0; i<input_array->length; i++)
    {
        char* value = (char*)(input_array->array[i]);
        if (strcmp(value, "(")==0)
        {
            int t = i;
            while (t<input_array->length)
            {
                if (strcmp(input_array->array[t], ")")==0)
                    break;
                t++;
            }
            if (t == input_array->length)
                e_call_error(ERR_NON_MATCHING_BRACKETS);

            int temp_i = i+1;
            
            array parenthesis_array = {malloc(8*(t-temp_i)), t-temp_i};
            for (int c=0; c<parenthesis_array.length; c++)
            {
                size_t string_length = strlen((char*)(input_array->array[c+temp_i]));

                parenthesis_array.array[c] = malloc(string_length);
                strcpy(parenthesis_array.array[c], input_array->array[c+temp_i]);
            }

            array new_nodes_array = make_nodes_array(&parenthesis_array);
            Node* parenthesis_node = node_tree_from_array(&new_nodes_array);

            for (int l=0; l<parenthesis_array.length+1; l++)
            {
                remove_at(input_array, i);
            }

            free_array(&parenthesis_array, true);
            free_array(&new_nodes_array, false);

            temp_output.array[i] = parenthesis_node;

            continue;
        }


        Node* new_node = malloc(sizeof(Node));

        if (strcmp(value, ")")==0)
        {
            e_call_error(ERR_NON_MATCHING_BRACKETS);
        }
        else if (strcmp(value, "*")==0)
        {
            new_node->is_operation = true;
            new_node->value        = OP_MULT;
        }
        else if (strcmp(value, "/")==0)
        {
            new_node->is_operation = true;
            new_node->value        = OP_DIV;
        }
        else if (strcmp(value, "^")==0)
        {
            new_node->is_operation = true;
            new_node->value        = OP_POW;
        }
        else if (strcmp(value, "+")==0)
        {
            new_node->is_operation = true;
            new_node->value        = OP_SUM;
        }
        else if (strcmp(value, "-")==0)
        {
            new_node->is_operation = true;
            new_node->value        = OP_SUB;
        }
        else
        {
            new_node->is_operation  = false;
            new_node->value         = stringToFloat(value);
        }

        new_node->left_child = NULL;
        new_node->right_child = NULL;
        temp_output.array[i] = new_node;
    }

    array output = {malloc(8*i), i};
    memcpy(output.array, temp_output.array, 8*i);

    free_array(&temp_output, false);

    return output;
}


int parse_and_node(char* input, int input_length)
{
    array input_array = parse_input(input);

    array nodes_array = make_nodes_array(&input_array);

    if (input_array.length == 0)
        free_array(&input_array, false);
    else
        free_array(&input_array, true);
    
    

    Node* root = node_tree_from_array(&nodes_array);
    resolve_node(root);
    printf("%f\n", root->value);

    free_array(&nodes_array, false);
    free_nodes(&root);
}
