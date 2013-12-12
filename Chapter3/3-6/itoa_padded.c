/**
 * Exercise 3-6, page 57
 * Упражнение 3.6, страница 78
 *
 * Write a version of itoa that accepts three arguments instead of two. The third
 * argument is a minimum field width; the converted number must be padded with blanks on the
 * left if necessary to make it wide enough.
 *
 * Напишите версию itoa, принимающую три аргумента вместо двух. Третий аргумент будет
 * минимальной шириной поля; преобразованное число следует дополнить пробелами слева,
 * если оно недостаточно длинное, чтобы заполнить это поле.
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

/** INT_MIN lenght = 10 + sign + '\0' */
#define MAX_LENGTH	12

void reverse (char s[]) {
	int i, j, c;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
		c = s[i], s[i] = s[j], s[j] = c;
}

void itoa_padded (int n, char s[], int padding) {
	int i, sign;

	sign = n;
	i = 0;
	/** we can use absolute values to correct the problem */
	do {
		s[i++] = abs (n % 10) + '0';
	} while ((abs(n /= 10)) > 0);
	if (sign < 0)
		s[i++] = '-';
	while (i < padding) {
		s[i++] = ' ';
	}
	s[i] = '\0';
	reverse(s);
}

int main (void) {
//	int n = INT_MIN;
	int n = 1;
	char s[MAX_LENGTH] = {0};

	itoa_padded(n,s, MAX_LENGTH-1);
	printf("number character string is \'%s\'\n", s);
	return 0;
}
