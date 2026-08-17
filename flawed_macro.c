#include <stdio.h>

/* Flawed Macro Scenario A: Simple arithmetic macro */
/* Intentionally unsafe: missing parentheses and evaluates side effects twice */
#define SQUARE(x) x * x

int main(void)
{
	int a = 5;
	int result;

	/* Flaw 1: Operator precedence bug when using expressions */
	result = SQUARE(a + 1); /* Expected (5+1)^2 = 36, actually evaluates to 5 + 1 * 5 + 1 = 11 */
	printf("SQUARE(5 + 1) = %d (Expected 36)\n", result);

	/* Flaw 2: Multiple evaluation bug with side effects */
	result = SQUARE(a++); /* Evaluates (a++) * (a++), causing undefined behavior */
	printf("SQUARE(a++) = %d, a = %d\n", result, a);

	return (0);
}
