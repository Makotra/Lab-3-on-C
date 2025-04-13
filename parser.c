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
		return 0;	 // Если оператор отсутствует, возвращаем минимальный приоритет.

	switch (op[0])
	{
	case '*':
		if (op[1] == '*')
			return 4;	 // Возведение в степень "**"
		return 3;		 // Умножение или деление: "*", "/"
	case '/':
	case '%':
		return 3;	 // Деление, остаток от деления
	case '+':
	case '-':
		return 2;	 // Сложение, вычитание
	case '^':
		return 1;	 // Побитовое XOR
	case '<':
	case '>':
		if (op[1] == op[0])
			return 1;	 // Сдвиг "<<", ">>"
		return 0;		 // Некорректный оператор
	default:
		return 0;	 // Неизвестный оператор
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
		return 4;	 // Ошибка инициализации памяти
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
