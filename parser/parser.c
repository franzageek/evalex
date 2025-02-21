#include "parser.h"
#include "rpn.h"
#include <string.h>

u8 check_syntax(token_t* tk)
{
    u16 err = 0;
    i16 brackets = 0;

    while (tk->type != TOKEN_NULL)
    {
        switch (tk->type)
        {
            case TOKEN_OPERATOR:
            {
                if ((tk+1)->type != TOKEN_LITERAL && (tk+1)->type != TOKEN_OPEN_BRACKET)
                    ++err;

                break;
            }
            case TOKEN_LITERAL:
            {
                if ((tk+1)->type == TOKEN_OPEN_BRACKET || (tk+1)->type == TOKEN_LITERAL)
                    ++err;

                break;
            }
            case TOKEN_OPEN_BRACKET:
            {
                if ((tk+1)->type != TOKEN_LITERAL && (tk+1)->type != TOKEN_OPEN_BRACKET)
                    ++err;

                ++brackets;
                break;
            }
            case TOKEN_CLOSE_BRACKET:
            {
                if ((tk+1)->type == TOKEN_OPEN_BRACKET || (tk+1)->type == TOKEN_LITERAL)
                    ++err;

                --brackets;
                break;
            }
            default:
            {
                ++err;
                break;
            }
        }
        ++tk;
    }

    return 
    (
        (brackets == 0 && err == 0) ?
            1
        : 
            0
    );
}

void identify_token(token_t** tk)
{
    if ((*tk)->type == TOKEN_LITERAL)
        move_to_stack(*tk, get_stack(STACK_OUTPUT));
    
    else if ((*tk)->type == TOKEN_OPERATOR)
    {
        if (check_precedence(*tk))
            move_to_stack(*tk, get_stack(STACK_OP));
            
        else
        {
            while (!check_precedence(*tk))
                pop_operator_to_output();
                
            move_to_stack(*tk, get_stack(STACK_OP));
        }   
    }
    else if ((*tk)->type == TOKEN_OPEN_BRACKET)
    {
        move_to_stack(*tk, get_stack(STACK_OP));
        ++(*tk);
        while ((*tk)->type != TOKEN_CLOSE_BRACKET)
        {
            identify_token(tk);
            ++(*tk);
        }
        memset(*tk, 0, sizeof(token_t));

        while (get_stack(STACK_OP)->top > 0 && get_top_item(STACK_OP)->type != TOKEN_OPEN_BRACKET)
            pop_operator_to_output();
        // ^ Handle "top == 0" case, "open_bracket_found" assumed

        memset(get_top_item(STACK_OP), 0, sizeof(token_t));

        if (get_stack(STACK_OP)->top > 0)
            --get_stack(STACK_OP)->top;
            
    }
    return;
}

token_t* expr_to_rpn(token_t* tk)
{
    
    u16 tk_count = 0;
    while (tk[tk_count].type != TOKEN_NULL)
        ++tk_count;

    init_stacks(tk_count+1);

    while (tk->type != TOKEN_NULL)
    {
        identify_token(&tk);
        ++tk;
    }
    while (get_stack(STACK_OP)->top > 0)
        pop_operator_to_output(); //Pop every remaining operator in the stack: there's no more operators to trigger any more pop's
    
    return stacks_cleanup();
}
