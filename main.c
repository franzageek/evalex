#include <stdio.h>
#include "tokens/tokens.h"

int main(void)
{
    const char* expr = "((1543 + 26543) * 3) / 1 - 4";
    printf("PARSeXP\n");
    printf("expr: %s\n", expr);
    token_t** tokens = tokenize_expr(expr);
    print_tokens(tokens);
    free_tokens(tokens);
    return 0;
}