#include <stdio.h>
#include <stdlib.h>
#include "tokens/tokens.h"
#include "parser/parser.h"

int main(void)
{
    const char* expr = "(1543 + 26543) * 3 * 5";
    printf("PARSeXP\n");
    printf("expr: %s\n", expr);
    token_t* tokens = tokenize_expr(expr);
    print_tokens(tokens);
    if (check_syntax(tokens))
        printf("Syntax OK\n");
    else
        printf("Syntax error\n");
    free(tokens);
    return 0;
}