#include <stdio.h>
#include "p_parser.h"

int main(int argc, char* argv[])
{
    char* cleaned_input;
    clean_input(&cleaned_input, argv, argc);

/*
    char* str1 = "Lmao";
    char* str2 = "L";

    int search_stack = 1;

    int len = strcspn(str1, str2);

    search_stack += len;

    len = strcspn(str1+search_stack, str2);

    search_stack += len;

    printf("First matched character is at %d\n", len);
    printf("%ld\n", strlen(str1));
    printf("%d\n", search_stack);
*/

    parse_and_node(cleaned_input, strlen(cleaned_input));

/*
    Node left_test2 = {NULL, NULL, false, 10};
    Node right_test2 = {NULL, NULL, false, 25};

    Node left_test1 = {&left_test2, &right_test2, true, OP_DIV};
    Node right_test1 = {NULL, NULL, false, 25};

    Node test_node = {&left_test1, &right_test1, true, OP_MULT};

    resolve_node(&test_node);
    printf("%f\n", test_node.value);
*/
    
    return 0;
}