#include "rpn.h"
#include <stdlib.h>
#include <string.h>

stack_t output_queue;
stack_t op_stack;

u8 init_stacks(u16 size)
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

stack_t* get_stack(stack_type_t type)
{
    return 
    (
        (type == STACK_OUTPUT) ? 
            &output_queue 
            
        : (type == STACK_OP) ? 
            &op_stack 
        
        : 
            NULL
    );
}

token_t* get_top_item(stack_type_t type)
{
    return 
    (
        (type == STACK_OUTPUT) ? 
            &(output_queue.stack[output_queue.top-1])
            
        : (type == STACK_OP) ? 
            &(op_stack.stack[op_stack.top-1]) 
        
        : 
            NULL
    );
}

u8 move_to_stack(token_t* tk, stack_t* stack)
{
    if (stack->top == stack->max-1)
        return 1;
    
    memcpy(&(stack->stack[stack->top]), tk, sizeof(token_t));
    ++stack->top;
    memset(tk, 0, sizeof(token_t));
    return 0;
}

u8 pop_operator_to_output(void)
{
    if (op_stack.top == 0)
        return 1;

    --op_stack.top;
    return move_to_stack(&(op_stack.stack[op_stack.top]), &output_queue);
}

u8 check_precedence(token_t* tk)
{
    if 
    ((
        op_stack.top > 0 
        &&
        tk->op.prec < op_stack.stack[op_stack.top-1].op.prec
    ) || (
        op_stack.top == 0
    ))
        return 1;

    else
        return 0;
}

token_t* stacks_cleanup(void)
{
    free(op_stack.stack);
    memset(&op_stack, 0, sizeof(stack_t));
    output_queue.max = output_queue.top = 0;
    return output_queue.stack;
}
