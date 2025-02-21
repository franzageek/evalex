#include <intdef.h>
#include <string.h>
#include "calc.h"

token_t* eval_expr(token_t* tk)
{
    token_t* tk_0 = tk;
    u16 token_count = 0;
    
    while (tk[token_count].type != TOKEN_NULL)
        ++token_count;
    
    tk += 2;
    u16 index = 0;
    i64 result = 0;
    
    while (tk->type != TOKEN_NULL)
    {
        
        if (tk->type == TOKEN_OPERATOR)
        {
            index = (tk - tk_0) / sizeof(token_t);
            switch (tk->operator.type)
            {
                case OPERATOR_ADD:
                {
                    result = (tk-2)->literal + (tk-1)->literal;
                    break;
                }
                case OPERATOR_SUB:
                {
                    result = (tk-2)->literal - (tk-1)->literal;
                    break;
                }
                case OPERATOR_MUL:
                {
                    result = (tk-2)->literal * (tk-1)->literal;
                    break;
                }
                case OPERATOR_DIV:
                {
                    result = (tk-2)->literal / (tk-1)->literal;
                    break;
                }
                default:
                    break;

            }
            (tk-2)->type = TOKEN_LITERAL;
            (tk-2)->literal = result;
            memmove(tk-1, tk+1, (token_count-index)*sizeof(token_t)); //Preserves null terminator
            --tk;
        }
        else
        {
            while (tk->type != TOKEN_OPERATOR && tk->type != TOKEN_NULL)
                ++tk;
        }
    }
    
    return tk_0;
}


//^ The uncommented version uses iterators
/*token_t* eval_expr(token_t* tk)
{
    
    u16 token_count = 0;
    
    while (tk[token_count].type != TOKEN_NULL)
    ++token_count;
    
    
    u16 index = 2;
    i64 result = 0;
    
    while (tk[index].type != TOKEN_NULL)
    {
        
        if (tk[index].type == TOKEN_OPERATOR)
        {
            switch (tk[index].operator.type)
            {
                case OPERATOR_ADD:
                {
                    result = tk[index-2].literal + tk[index-1].literal;
                    break;
                }
                case OPERATOR_SUB:
                {
                    result = tk[index-2].literal - tk[index-1].literal;
                    break;
                }
                case OPERATOR_MUL:
                {
                    result = tk[index-2].literal * tk[index-1].literal;
                    break;
                }
                case OPERATOR_DIV:
                {
                    result = tk[index-2].literal / tk[index-1].literal;
                    break;
                }
                default:
                    break;

            }
            tk[index-2].type = TOKEN_LITERAL;
            tk[index-2].literal = result;
            memmove(tk+index-1, tk+index+1, (token_count-index)*sizeof(token_t)); //Preserves null terminator
            --index;
        }
        else
        {
            while (tk[index].type != TOKEN_OPERATOR && tk[index].type != TOKEN_NULL)
                ++index;
        }
    }
    
    return tk;
}*/