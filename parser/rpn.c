#include "rpn.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef __DEBUG__
#include <assert.h>
#endif

stack_t output_queue;
stack_t op_stack;
stack_t* curr_stack = NULL;

u8 init_stacks(u8 size)
{
    output_queue.stack = (token_t*)calloc(size, sizeof(token_t));
    op_stack.stack = (token_t*)calloc(size, sizeof(token_t));
    
    if (output_queue.stack == NULL && op_stack.stack== NULL)
        return 3;
    else if (output_queue.stack == NULL)
        return 1;
    else if (op_stack.stack == NULL)
        return 2;

    output_queue.top = 0;
    op_stack.top = 0;

    output_queue.max = size;
    op_stack.max = size;

    return 0;
}

void free_stacks(void)
{
    free(output_queue.stack);
    free(op_stack.stack);
}

u8 move_to_stack(token_t* tk, stack_type_t stack_type)
{
    curr_stack = 
    (
        (stack_type == STACK_OUTPUT) ? 
            &output_queue 
            
        : (stack_type == STACK_OP_STACK) ? 
            &op_stack 
        
        : 
            NULL
    );

    if (curr_stack->top == curr_stack->max-1)
        return 1;
    
    memcpy(&curr_stack->stack[curr_stack->top], tk, sizeof(token_t));
    ++curr_stack->top;
    memset(tk, 0, sizeof(token_t));
    curr_stack = NULL;
    return 0;
}

u8 pop_operator_to_output(void)
{
    if (op_stack.top == 0)
        return 1;

    --op_stack.top;
    return move_to_stack(&op_stack.stack[op_stack.top], STACK_OUTPUT);
}

u8 check_precedence(token_t* in_tk)
{
    if 
    ((
        op_stack.top > 0 
        &&
        in_tk->operator.precedence < op_stack.stack[op_stack.top-1].operator.precedence
    ) || (
        op_stack.top == 0
    ))
        return 1;
    else
        return 0;
}

u8 is_op_stack_empty(void)
{
    return (op_stack.top == 0);
}

token_t* stacks_cleanup(void)
{
    #ifdef __DEBUG__
    assert(op_stack.top == 0);
    #endif
    
    free(op_stack.stack);
    memset(&op_stack, 0, sizeof(stack_t));
    output_queue.max = output_queue.top = 0;
    return output_queue.stack;
}
