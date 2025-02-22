#include "tokens.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

token_t* tokenize_expr(const char* expr)
{
    u16 token_queue_count = 8;
    u16 token_count = 0;
    u64 index = 0;
    char ch = '\0';
    
    token_t* tmp = NULL;
    token_t* tokens = (token_t*)calloc(token_queue_count+1, sizeof(token_t));
    if (tokens == NULL)
        return NULL;
    
    token_t* tk = NULL;
    
    while (expr[index] != '\0')
    {
        if (token_count == MAX_TOKENS-1)
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
            tk->type = TOKEN_LITERAL;
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
            tk->type = TOKEN_OPERATOR;
            tk->operator.type = 
            (
                (ch == '+') ? 
                    OPERATOR_ADD 

                : (ch == '-') ? 
                    OPERATOR_SUB 

                : (ch == '*') ?
                    OPERATOR_MUL 

                :
                    OPERATOR_DIV
            );

            tk->operator.precedence =
            (
                (ch == '+' || ch == '-') ? 
                    PREC_SUM 

                :
                    PREC_MUL
            );
        }
        else if (ch == '(' || ch == ')')
        {
            tk->type = (ch == '(') ? TOKEN_OPEN_BRACKET : TOKEN_CLOSE_BRACKET;
            tk->operator.type = OPERATOR_NULL;
            tk->operator.precedence = PREC_BRACKET;
        }
        else
        {
            tk->type = TOKEN_UNKNOWN;
            tk->value = ch;
        }

        if (token_count == token_queue_count)
        {
            
            token_queue_count *= 2;
            tmp = (token_t*)calloc((token_queue_count+1), sizeof(token_t));
            if (tmp != NULL)
            {
                memcpy(tmp, tokens, (token_count) * sizeof(token_t));
                free(tokens);
                tokens = tmp;
                tmp = NULL;
            }
            else
            {
                free(tk);
                return NULL;
            }
            #ifdef __DEBUG__
            printf("Successfully allocated %u+1 tokens as a post to %u+1.\n", token_queue_count, token_queue_count/2);
            #endif
        }

        memcpy(&tokens[token_count], tk, sizeof(token_t));
        free(tk);
        ++token_count;
        ++index;
    }
    #ifdef __DEBUG__
    printf("Successfully generated %u tokens.\n", token_count);
    #endif
    return tokens;
}

void print_tokens(token_t* tk)
{
    while (tk->type != TOKEN_NULL)
    {
        if (tk->type == TOKEN_LITERAL)
            printf("\e[7;33mliteral       :\e[0;33m %ld\e[0m\n", tk->literal);
        
        else if (tk->type == TOKEN_OPEN_BRACKET || tk->type == TOKEN_CLOSE_BRACKET)
        {
            printf("\e[7;34mbracket  ");
            if (tk->type == TOKEN_OPEN_BRACKET)
                printf("[OPB]:\e[0;34m (\e[0m\n");
            
            else
                printf("[CLB]:\e[0;34m )\e[0m\n");
            
        }
        
        else if (tk->type == TOKEN_OPERATOR)
        {
            printf("\e[7;36moperator ");
            if (tk->operator.type == OPERATOR_ADD)
                printf("[ADD]:\e[0;36m +\e[0m\n");
            
            else if (tk->operator.type == OPERATOR_SUB)
                printf("[SUB]:\e[0;36m -\e[0m\n");
            
            else if (tk->operator.type == OPERATOR_MUL)
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