/**
 * Exercise 3-5, page 56
 * Упражнение 3.5, страница 78
 * 
 * Write the function itob(n,s,b) that converts the integer n into a base b
 * character representation in the string s. In particular, itob(n,s,16) formats s as a
 * hexadecimal integer in s.
 *
 * Напишите функцию itob(n,s,b), которая бы преобразовывала целое число n в его
 * символьное представление в системе счисления с основанием b и помещала результат
 * в строку s. Например, вызов itob(n,s,16) должен представлять n в виде
 * шестнадцатиричного числа.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

/**
 * sizeof(int) * bits_in_byte + sign + '\0'
 * we use CHAR_BIT as the value of bits in byte
 */
#define MAX_LENGTH	sizeof(int)*CHAR_BIT+1+1

void reverse (char s[]) {
	int i, j, c;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
		c = s[i], s[i] = s[j], s[j] = c;
}

/**
 * this is the altered copy of itoa() from Ex.3.4
 * we return int in order to process error with wrong base
 */
int itob (int n, char s[], int b) {
	int i, sign;
	char symbols[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	/** the base should be limited */
	if (b < 2 || b > strlen(symbols)) {
		printf("error - not valid base for numeral system\n");
		return 1;
	}

	sign = n;
	i = 0;
	do {
		/** we set to char from our massive instead of calculations */
		s[i++] = symbols[abs (n % b)];
	} while ((abs(n /= b)) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
	return 0;
}

int main (void) {
	int res;
//	int n = -255;
	int n = INT_MIN;
	char s[MAX_LENGTH] = {0};

	res = itob(n,s,10);
	if (res)
		return res;
	printf("number character string (decimal) is \'%s\'\n", s);
	
	res = itob(n,s,8);
	if (res)
		return res;
	printf("number character string (octo-) is \'%s\'\n", s);

	res = itob(n,s,2);
	if (res)
		return res;
	printf("number character string (binary) is \'%s\'\n", s);

	res = itob(n,s,16);
	if (res)
		return res;
	printf("number character string (hexadecimal) is \'%s\'\n", s);

	res = itob(n,s,36);
	if (res)
		return res;
	printf("number character string (36-base) is \'%s\'\n", s);

	res = itob(n,s,1);
	if (res)
		return res;
	printf("number character string (1-base) is \'%s\'\n", s);

//	res = itob(n,s,37);
	return 0;
}
