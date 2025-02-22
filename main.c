#include <stdio.h>
#include <stdlib.h>
#include "include/evalex.h"

int main(void)
{
    //const char* expr = "4-(3+((725)*8/(56+2*6)+2)-(4/(1-1))+3*1)+4-(3+((746-25)*8/(56+2*6)+2)-(4/(1-1))+3*1)+4-(3+((746-25)*8/(56+2*6)+2)-(4/(1-1))+3*1)*4-(3+((746-25)*8/(56+2*6)+2)-(4/(1-1))+3*1)*4-(3+((746-25)*8/(56+2*6)+2)-(4/(1-1))+3*1)+4-(3+((746-25)*8/(56+2*6)+2)-(4/(1-1))+3*1)-4-(3+((746-25)*8/(56+2*6)+2)-(4/(1-1))+3*1)*4-(3+((746-25)*8/(56+2*6)+2)-(4/(1-1))+3*1)/4-(3+((746-25)*8/(56+2*6)+2)-(4/(1-1))+3*1)/4-(3+((746-25)*8/(56+2*6)+2)-(4/(1-1))+3*1)/4-(3+((746-25)*8/(56+2*6)+2)-(4/(1-1))+3*1)/4-(3+((746-25)*8/(56+2*6)+2)-(4/(1-1))+3*1)/4-(3-(4/(1-1))+3*1)+4-(3-(4/1))";
    const char* expr = "(3+4)*(3+5)/(5-((202-200)+1))";
    printf("eVALeX\n");
    printf("expr: %s\n", expr);
    token_t* tokens = tokenize_expr(expr);
    if (tokens == NULL)
    {
        fprintf(stderr, "Error: the expression is over %u tokens long.\n", MAX_TOKENS);
        return 1;
    }

    print_tokens(tokens);
    if (check_syntax(tokens))
    {
        printf("Syntax OK\n");

        token_t* rpn_expr = expr_to_rpn(tokens);
        print_tokens(rpn_expr);
        
        eval_expr(rpn_expr);
        printf("Evaluated expression:\n");
        print_tokens(rpn_expr);
        
        free(rpn_expr);
    }
    else
        printf("Syntax error\n");

    free(tokens);
    return 0;
}