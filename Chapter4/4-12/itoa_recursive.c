/**
 * Exercise 4-12, page 74
 * Упражнение 4.12, страница 101
 * 
 * Adapt the ideas of printd to write a recursive version of itoa ; that is, convert
 * an integer into a string by calling a recursive routine.
 *
 * Примените идеи, реализованные в printd, чтобы написать рекурсивную версию функции
 * itoa - преобразование целого числа в строку путем рекурсивного вызова.
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

/**
 * this is the copy of reverse() from Ex.3.4
 */
void reverse (char s[]) {
	int i, j, c;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
		c = s[i], s[i] = s[j], s[j] = c;
}

void printd(int n) {
	if (n < 0) {
		putchar('-');
		n = -n;
	}
	if (n / 10)
		printd(n / 10);
	putchar(n % 10 + '0');
}

void itoa_recursive(int n) {
	if (n < 0) {
		putchar('-');
//		n = -n;	// we can`t do it with INT_MIN
	}
	if (abs(n / 10))
		itoa_recursive(abs(n / 10));
	putchar(abs (n % 10) + '0');
}

/**
 * this is the copy of itoa_alt() from Ex.3.4
 */
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

/**
 * this is the copy of itoa() from Ex.3.4
 */
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
	printf("number character string is: ");
	itoa_recursive(n);
	printf("\n");
	return 0;
}
