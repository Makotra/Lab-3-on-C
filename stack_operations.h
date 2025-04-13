#ifndef STACK_OPERATIONS_H
#define STACK_OPERATIONS_H

#include <stddef.h>
#include <stdint.h>

typedef struct
{
	int32_t *data;
	size_t top;
	size_t capacity;
} Operand_Stack;

typedef struct
{
	char **data;
	size_t top;
	size_t capacity;
} Operator_Stack;

Operand_Stack *init_operand_stack();
void free_operand_stack(Operand_Stack *stack);
int push_operand(Operand_Stack *stack, int32_t value);
int pop_operand(Operand_Stack *stack, int32_t *value);

Operator_Stack *init_operator_stack();
void free_operator_stack(Operator_Stack *stack);
int push_operator(Operator_Stack *stack, const char *value);
int pop_operator(Operator_Stack *stack, const char **value);
const char *peek_char(const Operator_Stack *stack);

#endif
