#ifndef __EVALEX__
#define __EVALEX__ 1

#include <stdint.h>

#define MAX_TOKENS 512

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef struct
{
    enum 
    {
        TOKEN_NULL,
        TOKEN_UNKNOWN, 
        TOKEN_LITERAL,
        TOKEN_OPERATOR,
        TOKEN_OPEN_BRACKET,
        TOKEN_CLOSE_BRACKET,
    } type;
    union
    {
        i64 literal;
        struct 
        {
            enum 
            {
                OPERATOR_NULL,
                OPERATOR_ADD,
                OPERATOR_SUB,
                OPERATOR_MUL,
                OPERATOR_DIV,
            } type;
            enum 
            {
                PREC_MUL,
                PREC_SUM,
                PREC_BRACKET,
            } precedence;
        } operator;
        char value;
    };
} token_t;

/// @brief Convert an infix expression (in a `c_str` format) to a `token_t` array
/// @param  expr The `c_str` expression to tokenize
/// @return A pointer to the `token_t` array (must be freed after use)
token_t* tokenize_expr(const char* expr);

/// @brief Print the `token_t` array
/// @param  tk The `token_t` array to print
void print_tokens(token_t* tk);

/// @brief Check the syntax of an infix expression after being converted to a `token_t` array
/// @param  tk The `token_t` array to check
/// @return `1` if the syntax is correct, `0` otherwise
u8 check_syntax(token_t* tk);

/// @brief Convert an infix expression (in a `token_t` array format) to a `token_t` array in Reverse Polish Notation
/// @param  tk The `token_t` array expression to convert to RPN
/// @return A pointer to the `token_t` array in RPN (must be freed after use)
token_t* expr_to_rpn(token_t* tk);

/// @brief Evaluate an RPN expression in-place
/// @param tk The RPN expression to evaluate
/// @return A pointer to a `token_t` containing the result (same as input)
token_t* eval_expr(token_t* tk);

#endif