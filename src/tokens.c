#include "../include/evalex.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

token_t* tokenize_expr(const char* expr)
{
    u16 queue_count = 8;
    u16 tk_count = 0;
    u64 index = 0;
    char ch = '\0';
    
    token_t* tmp = NULL;
    token_t* tokens = (token_t*)calloc(queue_count+1, sizeof(token_t));
    if (tokens == NULL)
        return NULL;
    
    token_t* tk = NULL;
    
    while (expr[index] != '\0')
    {
        if (tk_count == MAX_TOKENS-1)
        {
            free(tokens);
            return NULL;
        }

        ch = expr[index];
        if (ch == ' ')
        {
            ++index;
            continue;
        }

        tk = (token_t*)calloc(1, sizeof(token_t));

        if (tk == NULL)
        {
            free(tokens);
            return NULL;
        }
        
        if (isdigit(ch))
        {
            tk->type = TK_LITERAL;
            tk->literal = 0;
            while (isdigit(ch))
            {
                tk->literal = tk->literal * 10 + (ch - '0');
                ch = expr[++index];
            }
            ch = expr[--index];
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            tk->type = TK_OPERATOR;
            tk->op.type = 
            (
                (ch == '+') ? 
                    OP_ADD 

                : (ch == '-') ? 
                    OP_SUB 

                : (ch == '*') ?
                    OP_MUL 

                :
                    OP_DIV
            );

            tk->op.prec =
            (
                (ch == '+' || ch == '-') ? 
                    PREC_SUM 

                :
                    PREC_MUL
            );
        }
        else if (ch == '(' || ch == ')')
        {
            tk->type = (ch == '(') ? TK_OPEN_BRACKET : TK_CLOSE_BRACKET;
            tk->op.type = OP_NULL;
            tk->op.prec = PREC_BRACKET;
        }
        else
        {
            tk->type = TK_UNKNOWN;
            tk->value = ch;
        }

        if (tk_count == queue_count)
        {
            
            queue_count *= 2;
            tmp = (token_t*)calloc((queue_count+1), sizeof(token_t));
            if (tmp != NULL)
            {
                memcpy(tmp, tokens, (tk_count) * sizeof(token_t));
                free(tokens);
                tokens = tmp;
                tmp = NULL;
            }
            else
            {
                free(tk);
                return NULL;
            }
            #ifdef DEBUG
            printf("Successfully allocated %u+1 tokens as a post to %u+1.\n", queue_count, queue_count/2);
            #endif
        }

        memcpy(&tokens[tk_count], tk, sizeof(token_t));
        free(tk);
        ++tk_count;
        ++index;
    }
    #ifdef DEBUG
    printf("Successfully generated %u tokens.\n", tk_count);
    #endif
    return tokens;
}

void print_tokens(token_t* tk)
{
    while (tk->type != TK_NULL)
    {
        if (tk->type == TK_LITERAL)
            printf("\e[7;33mliteral       :\e[0;33m %ld\e[0m\n", tk->literal);
        
        else if (tk->type == TK_OPEN_BRACKET || tk->type == TK_CLOSE_BRACKET)
        {
            printf("\e[7;34mbracket  ");
            if (tk->type == TK_OPEN_BRACKET)
                printf("[OPB]:\e[0;34m (\e[0m\n");
            
            else
                printf("[CLB]:\e[0;34m )\e[0m\n");
            
        }
        
        else if (tk->type == TK_OPERATOR)
        {
            printf("\e[7;36moperator ");
            if (tk->op.type == OP_ADD)
                printf("[ADD]:\e[0;36m +\e[0m\n");
            
            else if (tk->op.type == OP_SUB)
                printf("[SUB]:\e[0;36m -\e[0m\n");
            
            else if (tk->op.type == OP_MUL)
                printf("[MUL]:\e[0;36m *\e[0m\n");
            
            else
                printf("[DIV]:\e[0;36m /\e[0m\n");   
        }
        else
            printf("\e[7;31munknown       :\e[0;31m %c\e[0m\n", tk->value);
        
        ++tk;
    }
    return;
}