#include <stdio.h>
#include "p_parser.h"

int main(int argc, char* argv[])
{
    char* cleaned_input;
    clean_input(&cleaned_input, argv, argc);
    parse_and_node(cleaned_input, strlen(cleaned_input));

    printf("%f\n", stringToFloat("3456"));


    Node left_test2 = {NULL, NULL, false, 10};
    Node right_test2 = {NULL, NULL, false, 25};

    Node left_test1 = {&left_test2, &right_test2, true, OP_DIV};
    Node right_test1 = {NULL, NULL, false, 25};

    Node test_node = {&left_test1, &right_test1, true, OP_MULT};

    resolve_node(&test_node);
    printf("%f\n", test_node.value);
    
    return 0;
}