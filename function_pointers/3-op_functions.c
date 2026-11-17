#include "3-calc.h"
/**
 * get_op_func - selects the correct function to perform the operation
 * @s: The operator passed as an argument
 *
 * Return: A pointer to the function corresponding to the operator given as a
 * parameter. If the operator is not recognized, it returns NULL.
 */
int (*get_op_func(char *s))(int, int)
{
	int op_add(int a, int b)
		return (a + b);
	int op_sub(int a, int b)
		return (a - b);
	int op_mul(int a, int b)
		return (a * b);
	int op_div(int a, int b)
		if (a == 0 || b == 0)
			return (0);
		return (a / b);
	int op_mod(int a, int b)
		return(a % b);
