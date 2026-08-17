#include <stdio.h>
#include <stdlib.h>

/* 
 * Requirement 1: Complete include guards 
 * Requirement 2: Clean #else fallback disabling debug logs in release
 * Requirement 3: Professional logging macro outputting __FILE__, __LINE__, and timestamp
 */

#ifndef DEBUG_CONFIG_H
#define DEBUG_CONFIG_H

/* Safe macro with proper parameter wrapping to prevent precedence errors */
#define SQUARE(x) ((x) * (x))

#ifdef DEBUG_MODE
	#define LOG_DEBUG(fmt, ...) \
		fprintf(stderr, "[DEBUG] [%s:%d - %s %s]: " fmt "\n", \
			__FILE__, __LINE__, __DATE__, __TIME__, ##__VAARGS__)
#else
	#define LOG_DEBUG(fmt, ...) ((void)0)
#endif

#endif /* DEBUG_CONFIG_H */

int main(void)
{
	int a = 5;
	int result;

	LOG_DEBUG("Program starting with variable a = %d", a);

	/* Safe evaluation with expression */
	result = SQUARE(a + 1);
	printf("SQUARE(a + 1) = %d\n", result);

	LOG_DEBUG("Program execution complete");

	return (0);
}
