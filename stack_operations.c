#include "stack_operations.h"

#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16

Operand_Stack *init_operand_stack()
{
	Operand_Stack *stack = malloc(sizeof(Operand_Stack));
	if (!stack)
		return NULL;
	stack->data = malloc(INITIAL_CAPACITY * sizeof(int32_t));
	if (!stack->data)
	{
		free(stack);
		return NULL;
	}
	stack->capacity = INITIAL_CAPACITY;
	stack->top = 0;
	return stack;
}

void free_operand_stack(Operand_Stack *stack)
{
	free(stack->data);
	free(stack);
}

int push_operand(Operand_Stack *stack, int32_t value)
{
	if (stack->top >= stack->capacity)
	{
		size_t new_capacity = stack->capacity * 2;
		int32_t *new_data = realloc(stack->data, new_capacity * sizeof(int32_t));
		if (!new_data)
			return 4;
		stack->data = new_data;
		stack->capacity = new_capacity;
	}
	stack->data[stack->top++] = value;
	return 0;
}

int pop_operand(Operand_Stack *stack, int32_t *value)
{
	if (stack->top == 0)
		return 3;
	*value = stack->data[--stack->top];
	return 0;
}

Operator_Stack *init_operator_stack()
{
	Operator_Stack *stack = malloc(sizeof(Operator_Stack));
	if (!stack)
		return NULL;
	stack->data = malloc(INITIAL_CAPACITY * sizeof(char *));
	if (!stack->data)
	{
		free(stack);
		return NULL;
	}
	stack->capacity = INITIAL_CAPACITY;
	stack->top = 0;
	return stack;
}

void free_operator_stack(Operator_Stack *stack)
{
	for (size_t i = 0; i < stack->top; ++i)
	{
		free(stack->data[i]);
	}
	free(stack->data);
	free(stack);
}

int push_operator(Operator_Stack *stack, const char *value)
{
	if (stack->top >= stack->capacity)
	{
		size_t new_capacity = stack->capacity * 2;
		char **new_data = realloc(stack->data, new_capacity * sizeof(char *));
		if (!new_data)
			return 4;
		stack->data = new_data;
		stack->capacity = new_capacity;
	}
	stack->data[stack->top] = strdup(value);
	if (!stack->data[stack->top])
		return 4;
	stack->top++;
	return 0;
}

int pop_operator(Operator_Stack *stack, const char **value)
{
	if (stack->top == 0)
		return 3;
	*value = stack->data[--stack->top];
	free(stack->data[stack->top]);
	return 0;
}

const char *peek_char(const Operator_Stack *stack)
{
	if (stack->top == 0)
		return NULL;
	return stack->data[stack->top - 1];
}
