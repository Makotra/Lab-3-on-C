#include "parser.h"
#include "stdint.h"

#include <stdio.h>
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Error: Program expects exactly one argument - the expression to evaluate.\n");
		return 4;
	}

	int32_t result;
	int status = parsing(argv[1], &result);

	switch (status)
	{
	case 1:
		fprintf(stderr, "Error: Unsupported operation.\n");
		return status;
	case 2:
		fprintf(stderr, "Error: Division by zero, negative exponent, invalid shift, or integer overflow.\n");
		return status;
	case 3:
		fprintf(stderr, "Error: Parsing error (mismatched parentheses or missing operands).\n");
		return status;
	case 4:
		fprintf(stderr, "Error: An unexpected error occurred.\n");
		return status;
	default:
		printf("%d\n", result);
	}
	return 0;
}
