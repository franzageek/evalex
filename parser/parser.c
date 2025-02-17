#include "parser.h"
#include "rpn.h"
#include <stdlib.h>

u8 check_syntax(token_t* tokens)
{
    u8 unknowns = 0;
    u8 operators = 0;
    u8 literals = 0;
    i8 brackets = 0;

    for (u8 i = 0; tokens[i].type != TOKEN_NULL; ++i)
    {
        switch (tokens[i].type)
        {
            case TOKEN_OPERATOR:
            {
                if (tokens[i+1].type != TOKEN_LITERAL)
                    ++operators;

                break;
            }
            case TOKEN_LITERAL:
            {
                if (tokens[i+1].type != TOKEN_NULL && tokens[i+1].type == TOKEN_LITERAL)
                    ++literals;

                break;
            }
            case TOKEN_OPEN_BRACKET:
            {
                if (tokens[i+1].type != TOKEN_LITERAL)
                    ++operators;

                ++brackets;
                break;
            }
            case TOKEN_CLOSE_BRACKET:
            {
                if (tokens[i+1].type != TOKEN_NULL && tokens[i+1].type == TOKEN_LITERAL)
                    ++literals;

                --brackets;
                break;
            }
            case TOKEN_UNKNOWN:
            {
                ++unknowns;
                break;
            }
        }
    }

    return 
    (
        (brackets == 0 && unknowns == 0 && literals == 0 && operators == 0) ?
            1
        : 
            0
    );
}

token_t* expr_to_rpn(token_t* tokens)
{
    token_t* tk = tokens;
    u8 token_count = 0;
    while (tokens[token_count].type != TOKEN_NULL)
        ++token_count;

    init_stacks(token_count+1);

    while (tk->type != TOKEN_NULL)
    {
        if (tk->type == TOKEN_LITERAL)
            move_to_stack(tk, STACK_OUTPUT);
        
        else if (tk->type == TOKEN_OPERATOR)
        {
            if (check_precedence(tk))
                move_to_stack(tk, STACK_OP_STACK);
                
            else
            {
                while (!check_precedence(tk))
                    pop_operator_to_output();
                
                move_to_stack(tk, STACK_OP_STACK);
            }   
        }
        ++tk;
    }
    while (!is_op_stack_empty())
        pop_operator_to_output(); //Pop every remaining operator in the stack: there's no more operators to trigger any more pop's
    
    return stacks_cleanup();
}
