#include "tokens.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

token_t* tokenize_expr(const char* expr)
{
    u8 token_queue_count = 8;
    u8 token_count = 0;
    u64 index = 0;
    char ch = '\0';
    
    token_t* tokens = (token_t*)calloc(token_queue_count+1, sizeof(token_t));
    if (tokens == NULL)
        return NULL;
    
    token_t* tk = NULL;

    while (expr[index] != '\0' /*&& token_count < MAX_TOKENS*/)
    {
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
            tk->operator = 
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
        }
        else if (ch == '(' || ch == ')')
        {
            tk->type = (ch == '(') ? TOKEN_OPEN_BRACKET : TOKEN_CLOSE_BRACKET;
            tk->value = ch;
        }
        else
        {
            tk->type = TOKEN_UNKNOWN;
            tk->value = ch;
        }

        if (token_count == token_queue_count)
        {
            token_queue_count *= 2;
            tokens = (token_t*)realloc(tokens, (token_queue_count+1) * sizeof(token_t));
            memset(&tokens[token_count+1], 0, sizeof(token_t)*(token_queue_count+1-token_count+1));
        }

        memcpy(&tokens[token_count], tk, sizeof(token_t));
        free(tk);
        ++token_count;
        ++index;
    }
    return tokens;
}

void print_tokens(token_t* tokens)
{
    u8 i = 0;
    while (tokens[i].type != TOKEN_NULL)
    {
        if (tokens[i].type == TOKEN_LITERAL)
            printf("\e[7;33mliteral       :\e[0;33m %lu\e[0m\n", tokens[i].literal);

        else if (tokens[i].type == TOKEN_OPEN_BRACKET || tokens[i].type == TOKEN_CLOSE_BRACKET)
        {
            printf("\e[7;34mbracket  ");
            if (tokens[i].type == TOKEN_OPEN_BRACKET)
                printf("[OPB]:");

            else
                printf("[CLB]:");

            printf("\e[0;34m %c\e[0m\n", tokens[i].value);
        }

        else if (tokens[i].type == TOKEN_OPERATOR)
        {
            printf("\e[7;36moperator ");
            if (tokens[i].operator == OPERATOR_ADD)
                printf("[ADD]:\e[0;36m +\e[0m\n");

            else if (tokens[i].operator == OPERATOR_SUB)
                printf("[SUB]:\e[0;36m -\e[0m\n");

            else if (tokens[i].operator == OPERATOR_MUL)
                printf("[MUL]:\e[0;36m *\e[0m\n");

            else
                printf("[DIV]:\e[0;36m /\e[0m\n");   
        }
        else
            printf("\e[7;31munknown       :\e[0;31m %c\e[0m\n", tokens[i].value);

        ++i;
    }
    return;
}
/*
void free_tokens(token_t** tokens)
{
    u8 i = 0;
    while (tokens[i] != NULL)
    {
        free(tokens[i]);
        ++i;
    }
    free(tokens);
    return;
}*/