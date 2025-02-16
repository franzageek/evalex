#ifndef TOKENS_H
#define TOKENS_H

#include <intdef.h>

#define MAX_TOKENS 256

typedef enum
{
    TOKEN_LITERAL,
    TOKEN_OPERATOR,
    TOKEN_OPEN_BRACKET,
    TOKEN_CLOSE_BRACKET,
    TOKEN_UNKNOWN
} token_type_t;

typedef struct
{
    token_type_t type;
    union
    {
        u64 literal;
        char value;
    };
} token_t;

token_t** tokenize_expr(const char* exp);
void print_tokens(token_t** tokens);
void free_tokens(token_t** tokens);

#endif // TOKENS_H
