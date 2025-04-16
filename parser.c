#include "parser.h"

#include "counter.h"
#include "stack_operations.h"

#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Определение приоритетов операторов
static int priority(const char *op)
{
	if (!op)
		return 0;	 

	switch (op[0])
	{
	case '*':
		if (op[1] == '*')
			return 4;	 
		return 3;		 
	case '/':
	case '%':
		return 3;	 
	case '+':
	case '-':
		return 2;	 
	case '^':
		return 1;	 
	case '<':
	case '>':
		if (op[1] == op[0])
			return 1;	 
		return 0;		 
	default:
		return 0;	 
	}
}

// Основной парсер
int parsing(const char *expr, int32_t *result)
{
	Operand_Stack *values = init_operand_stack();
	Operator_Stack *operators = init_operator_stack();
	if (!values || !operators)
	{
		free_operand_stack(values);
		free_operator_stack(operators);
		return 4;	 
	}

	int status = 0;
	const char *token = expr;

	while (*token)
	{
		char current = *token;
		char next = *(token + 1);

		if (isspace(current))
		{
			token++;
			continue;
		}

		if (isdigit(current) || (current == '-' && isdigit(next)))
		{
			int32_t value = strtol(token, (char **)&token, 10);
			if (push_operand(values, value) != 0)
			{
				status = 4;
				break;
			}
		}
		else if (current == '(')
		{
			if (push_operator(operators, "(") != 0)
			{
				status = 4;
				break;
			}
			token++;
		}
		else if (current == ')')
		{
			while (operators->top > 0 && strcmp(peek_char(operators), "(") != 0)
			{
				if ((status = process_operator(values, operators, &status)) != 0)
				{
					break;
				}
