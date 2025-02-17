#include <stdio.h>
#include <stdlib.h>
#include "tokens/tokens.h"
#include "parser/parser.h"

int main(void)
{
    const char* expr = "1 + 2 * 3 - 4 / 3 / 5 - 7 * 3 + 1 + 2 + 3 - 4 - 2";
    printf("PARSeXP\n");
    printf("expr: %s\n", expr);
    token_t* tokens = tokenize_expr(expr);
    print_tokens(tokens);
    if (check_syntax(tokens))
    {
        printf("Syntax OK\n");
        token_t* rpn_expr = expr_to_rpn(tokens);
        print_tokens(rpn_expr);
        free(rpn_expr);
    }
    else
        printf("Syntax error\n");

    free(tokens);
    return 0;
}