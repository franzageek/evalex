#include "tokens.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

token_t** tokenize_expr(const char* expr)
{
    u8 token_queue_count = 8;
    u8 token_count = 0;
    u64 index = 0;
    char ch = '\0';
    
    token_t** tokens = (token_t**)malloc(token_queue_count * sizeof(token_t*));
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

        tk = (token_t*)malloc(sizeof(token_t));

        if (tk == NULL)
        {
            for (u8 j = 0; j < token_count; ++j)
                free(tokens[j]);

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
            tk->value = ch;
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
            tokens = (token_t**)realloc(tokens, token_queue_count * sizeof(token_t*));
        }

        tokens[token_count] = tk;

        ++token_count;
        ++index;
    }
    return tokens;
}

void print_tokens(token_t** tokens)
{
    u8 i = 0;
    while (tokens[i] != NULL)
    {
        if (tokens[i]->type == TOKEN_LITERAL)
            printf("literal: %lu\n", tokens[i]->literal);

        else if (tokens[i]->type == TOKEN_OPEN_BRACKET || tokens[i]->type == TOKEN_CLOSE_BRACKET)
            printf("bracket: %c\n", tokens[i]->value);

        else if (tokens[i]->type == TOKEN_OPERATOR)
            printf("operator: %c\n", tokens[i]->value);

        else
            printf("\e[7;31munknown:\e[0;31m %c\e[0m\n", tokens[i]->value);

        ++i;
    }
    return;
}

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
}