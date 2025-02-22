#include <string.h>
#include "../evalex.h"

token_t* eval_expr(token_t* tk)
{
    token_t* tk_0 = tk;
    u16 token_count = 0;
    
    while (tk[token_count].type != TK_NULL)
        ++token_count;
    
    tk += 2;
    u16 index = 0;
    i64 result = 0;
    
    while (tk->type != TK_NULL)
    {
        if (tk->type == TK_OPERATOR)
        {
            index = (tk - tk_0) / sizeof(token_t);
            switch (tk->op.type)
            {
                case OP_ADD:
                {
                    result = (tk-2)->literal + (tk-1)->literal;
                    break;
                }
                case OP_SUB:
                {
                    result = (tk-2)->literal - (tk-1)->literal;
                    break;
                }
                case OP_MUL:
                {
                    result = (tk-2)->literal * (tk-1)->literal;
                    break;
                }
                case OP_DIV:
                {
                    result = (tk-2)->literal / (tk-1)->literal;
                    break;
                }
                default:
                    break;

            }
            (tk-2)->type = TK_LITERAL;
            (tk-2)->literal = result;
            memmove(tk-1, tk+1, (token_count-index)*sizeof(token_t)); //Preserves null terminator
            --tk;
        }
        else
        {
            while (tk->type != TK_OPERATOR && tk->type != TK_NULL)
                ++tk;
        }
    }
    
    return tk_0;
}


//^ The uncommented version uses iterators
/*token_t* eval_expr(token_t* tk)
{
    
    u16 token_count = 0;
    
    while (tk[token_count].type != TK_NULL)
    ++token_count;
    
    
    u16 index = 2;
    i64 result = 0;
    
    while (tk[index].type != TK_NULL)
    {
        
        if (tk[index].type == TK_OPERATOR)
        {
            switch (tk[index].op.type)
            {
                case OP_ADD:
                {
                    result = tk[index-2].literal + tk[index-1].literal;
                    break;
                }
                case OP_SUB:
                {
                    result = tk[index-2].literal - tk[index-1].literal;
                    break;
                }
                case OP_MUL:
                {
                    result = tk[index-2].literal * tk[index-1].literal;
                    break;
                }
                case OP_DIV:
                {
                    result = tk[index-2].literal / tk[index-1].literal;
                    break;
                }
                default:
                    break;

            }
            tk[index-2].type = TK_LITERAL;
            tk[index-2].literal = result;
            memmove(tk+index-1, tk+index+1, (token_count-index)*sizeof(token_t)); //Preserves null terminator
            --index;
        }
        else
        {
            while (tk[index].type != TK_OPERATOR && tk[index].type != TK_NULL)
                ++index;
        }
    }
    
    return tk;
}*/