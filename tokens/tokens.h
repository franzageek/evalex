#ifndef TOKENS_H
#define TOKENS_H

#include <intdef.h>

#define MAX_TOKENS 512

typedef enum
{
    OPERATOR_NULL,
    OPERATOR_ADD,
    OPERATOR_SUB,
    OPERATOR_MUL,
    OPERATOR_DIV,
} operator_type_t;

typedef enum
{
    PREC_MUL,
    PREC_SUM,
    PREC_BRACKET,
} precedence_type_t;

typedef struct 
{
    operator_type_t type;
    precedence_type_t precedence;
} operator_t;


typedef enum
{
    TOKEN_NULL,
    TOKEN_UNKNOWN, 
    TOKEN_LITERAL,
    TOKEN_OPERATOR,
    TOKEN_OPEN_BRACKET,
    TOKEN_CLOSE_BRACKET,
} token_type_t;


typedef struct
{
    token_type_t type;
    union
    {
        i64 literal;
        operator_t operator;
        char value;
    };
} token_t;

token_t* tokenize_expr(const char* exp);
void print_tokens(token_t* tk);

#endif // TOKENS_H
