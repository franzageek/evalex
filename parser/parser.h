#ifndef PARSER_H
#define PARSER_H

#include <intdef.h>
#include "../tokens/tokens.h"

u8 check_syntax(token_t* tk);
token_t* expr_to_rpn(token_t* tk);

#endif // PARSER_H