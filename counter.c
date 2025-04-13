#include "counter.h"

#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static int application_of_operations(int32_t a, int32_t b, const char *op, int *status)
{
	if (strcmp(op, "**") == 0)
	{
		if (b < 0)
		{
			*status = 2;
			return 0;
		}
		return (int32_t)pow(a, b);
	}
	switch (op[0])
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return b == 0 ? (*status = 2, 0) : a / b;
	case '%':
		return b == 0 ? (*status = 2, 0) : a % b;
	case '&':
		return a & b;
	case '|':
		return a | b;
	case '^':
		return a ^ b;
	case '<':
		if (b < 0 || b > 32)
		{
			*status = 2;
			return 0;
		}
		return a << b;
	case '>':
		if (b < 0 || b > 32)
		{
			*status = 2;
			return 0;
		}
		return a >> b;
	case '~':
		return ~a;
	default:
		*status = 1;
		return 0;
	}
}

int process_operator(Operand_Stack *values, Operator_Stack *operators, int *status)
{
	int32_t b = 0, a = 0;
	const char *op;
	if (pop_operator(operators, &op) != 0)
		return 3;

	if (strcmp(op, "~") == 0)
	{
		if (pop_operand(values, &a) != 0)
			return 3;
		a = application_of_operations(a, 0, op, status);
	}
	else
	{
		if (pop_operand(values, &b) != 0 || pop_operand(values, &a) != 0)
			return 3;
		a = application_of_operations(a, b, op, status);
	}
	if (*status != 0)
		return *status;
	return push_operand(values, a);
}
