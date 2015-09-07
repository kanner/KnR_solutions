/**
 * Exercise 3-4, page 56
 * Упражнение 3.4, страница 78
 * 
 * In a two's complement number representation, our version of itoa does not
 * handle the largest negative number, that is, the value of n equal to -(2^wordsize - 1). Explain why not.
 * Modify it to print that value correctly, regardless of the machine on which it runs.
 *
 * В представлении чисел с помощью дополнения до двойки наша версия функции itoa не умеет обрабатывать
 * самое большое по модулю отрицательное число, т.е. значение n, равное -(2^длина_слова - 1). Объясните,
 * почему это так. Доработайте функцию так, чтобы она выводила это число правильно независимо от
 * системы, в которой она работает
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

/** INT_MAX lenght = 10 + sign + '\0' */
#define MAX_LENGTH	12

void reverse (char s[]) {
	int i, j, c;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
		c = s[i], s[i] = s[j], s[j] = c;
}

void itoa_alt (int n, char s[]) {
	int i, sign;

	sign = n;
	i = 0;
	/** we can use absolute values to correct the problem */
	do {
		s[i++] = abs (n % 10) + '0';
	} while ((abs(n /= 10)) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void itoa (int n, char s[]) {
	int i, sign;

	/**
	 * INT_MIN doesn`t have positive equivalent
	 */
	/** record sign */
	if ((sign = n) < 0)
		/** make n positive */
		n = -n;
	i = 0;
	/** generate digits in reverse order */
	do {
		/** get next digit */
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);	/** delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

int main (void) {
	int n = INT_MIN;
	char s[MAX_LENGTH] = {0};

	itoa_alt(n,s);
	printf("number character string is \'%s\'\n", s);
	return 0;
}
