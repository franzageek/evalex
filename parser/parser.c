#include "parser.h"
#include <stdlib.h>

u8 check_syntax(token_t* tokens)
{
    u8 unknowns = 0;
    u8 operators = 0;
    u8 literals = 0;
    i8 brackets = 0;

    for (u8 i = 0; tokens[i].type != TOKEN_NULL; ++i)
    {
        switch (tokens[i].type)
        {
            case TOKEN_OPERATOR:
            {
                if (tokens[i+1].type != TOKEN_NULL && tokens[i+1].type == TOKEN_OPERATOR)
                    ++operators;

                break;
            }
            case TOKEN_LITERAL:
            {
                if (tokens[i+1].type != TOKEN_NULL && tokens[i+1].type == TOKEN_LITERAL)
                    ++literals;

                break;
            }
            case TOKEN_OPEN_BRACKET:
            {
                if (tokens[i+1].type != TOKEN_NULL && tokens[i+1].type == TOKEN_OPERATOR)
                    ++operators;

                ++brackets;
                break;
            }
            case TOKEN_CLOSE_BRACKET:
            {
                if (tokens[i+1].type != TOKEN_NULL && tokens[i+1].type == TOKEN_LITERAL)
                    ++literals;

                --brackets;
                break;
            }
            case TOKEN_UNKNOWN:
            {
                ++unknowns;
                break;
            }
        }
    }

    return 
    (
        (brackets == 0 && unknowns == 0 && literals == 0 && operators == 0) ?
            1
        : 
            0
    );
}