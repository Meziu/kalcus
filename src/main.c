#include <stdio.h>
#include "p_parser.h"

int main(int argc, char* argv[])
{
    char* cleaned_input;
    clean_input(&cleaned_input, argv, argc);

    parse_and_node(cleaned_input, strlen(cleaned_input));
    
    return 0;
}