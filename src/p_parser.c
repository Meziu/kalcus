#include "p_parser.h"

char* all_symbols       = "*/^+-.()";
char* operation_symbols = "*/^+-";

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

    // this horrible crap is used until I implement parenthesis support
    remove_all_char(*end_str, '(');
    remove_all_char(*end_str, ')');

    // control if now the string is ok, otherwise throw a tantrum
    check_valid_characters(*end_str);
}


int fill_operations_string(char* operations_str, const char* input_str)
{
    int found_at = chars_in_string(input_str, operation_symbols, strlen(operation_symbols), 0);
    int i = 0;
    while (found_at != -1)
    {
        operations_str[i] = input_str[found_at];
        found_at = chars_in_string(input_str, operation_symbols, strlen(operation_symbols), found_at+1);
        i++;
    }
    return i;
}

int get_input_array(char* input, char* output[])
{
    char* temp_input = malloc(strlen(input));
    strcpy(temp_input, input);
    printf("%s\n", temp_input);

    char* current_string = strtok(temp_input, operation_symbols);
    int i = 0;

    while (current_string != NULL)
    {
        output[i++] = current_string;
        current_string = strtok(NULL, operation_symbols);
    }
    return i;
}

int parse_and_node(char* input, int input_length)
{
    /* get all of the operations and store them in an *oversized* string, 
       to then re-store them in a smaller one */
    char* temp_operation_findings = malloc(input_length);
    int operation_findings_len = fill_operations_string(temp_operation_findings, input);
    char* operation_findings = malloc(operation_findings_len);

    memcpy(operation_findings, temp_operation_findings, operation_findings_len);
    free(temp_operation_findings);


    // same as above, but for the values
    char** temp_values_array = malloc(input_length*8);
    int values_array_len = get_input_array(input, temp_values_array);
    char** values_array = malloc(values_array_len);

    memcpy(values_array, temp_values_array, values_array_len*8);
    free(temp_values_array);


    // check if the number of "breaks" in the values array matches the number of operations inputted
    if (operation_findings_len != values_array_len-1)
        e_call_error(ERR_INVALID_INPUT);
    

    printf("OPERATIONS FOUND: %s\n", operation_findings);
    for (int i=0; i<values_array_len; i++)
        printf("%s\n", values_array[i]);
}