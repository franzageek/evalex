#ifndef PARSER_H
#define PARSER_H

#include <intdef.h>
#include "../tokens/tokens.h"

u8 check_syntax(token_t* tokens);
token_t* expr_to_rpn(token_t* tokens);

#endif // PARSER_H