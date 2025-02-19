#ifndef RPN_H
#define RPN_H

#include <intdef.h>
#include "../tokens/tokens.h"

typedef enum
{
    STACK_INPUT,
    STACK_OUTPUT,
    STACK_OP
} stack_type_t;

typedef struct
{
    token_t* stack;
    u8 max;
    u8 top;
} stack_t;

u8 init_stacks(u8 size);
stack_t* get_stack(stack_type_t type);
token_t* get_top_item(stack_type_t type);
u8 move_to_stack(token_t* tk, stack_t* stack);
u8 pop_operator_to_output(void);
u8 check_precedence(token_t* in_tk);
/*u8 is_op_stack_empty(void);*/
token_t* stacks_cleanup(void);  //Maybe rework RPN API

#endif // RPN_H