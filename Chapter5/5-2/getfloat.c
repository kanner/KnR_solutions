/**
 * Exercise 5-2, page 81
 * Упражнение 5.2, страница 109
 * 
 * Write getfloat, the floating-point analog of getint. What type does getfloat
 * return as its function value?
 *
 * Напишите функцию getfloat, аналог getint для вещественных чисел.
 * Данные какого типа должна возвращать функция getfloat?
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>

/** size of buffer for getch/ungetch */
#define BUFSIZE 100

/** buffer for ungetch */
char buf[BUFSIZE];
/** next free position in buf */
int  bufp = 0;

/** get a (possibly pushed back) character */
int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/** push character back on input */
void ungetch(int c) {
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else if (c != EOF)
		buf[bufp++] = c;
}

int getfloat(float *pn) {
	double power = 1.0;
	int c, sign, exp_sign, exp;
	int exp_char;

	while (isspace(c = getch()))
		/** skip space symbpols */
		;
	
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		/** not number */
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		c = getch();
		if (!isdigit(c)) {
			/** if '+' or '-' are not followed by digit */
			ungetch(c);
			ungetch(sign == 1 ? '+' : '-');
			return 0;
		}
	}
	/** integer */
	for (*pn = 0.0; isdigit(c); c = getch())
		*pn = 10.0 * *pn + (c - '0');
	/** fraction */
	if (c == '.') {
		c = getch();
		for (power = 1.0; isdigit(c); c = getch()) {
			*pn = 10.0 * *pn + (c - '0');
			power *= 10.0;
		}
//		*pn *= sign / power;
	}

	exp_char = (c == 'E') ? 1 : 0;
	/** exponent */
	if (c == 'e' || c == 'E') {
		c = getch();
		exp_sign = (c == '-') ? -1 : 1;
		if (c == '+' || c == '-') {
			c = getch();
			if (!isdigit(c)) {
				/** if '+' or '-' are not followed by digit */
				ungetch(c);
				ungetch(sign == 1 ? '+' : '-');
			}
		}
		/** if 'E' or 'e' are not followed by digit */
		else if (!isdigit(c)) {
			ungetch(c);
			ungetch(exp_char == 0 ? 'e' : 'E');
		}
		for (exp = 0.0; isdigit(c); c = getch())
			exp = 10.0 * exp + (c - '0');
		*pn *= (sign / power) * pow(10, exp_sign * exp);
	}
	else
		*pn *= sign / power;
	if (c != EOF)
		ungetch(c);
	return c;
}

int main (void) {
	int res;
	float x;

	res = getfloat(&x);
	if (res > 0)
		printf("getfloat() got float: %f\n", x);
	else if (res == EOF)
		printf("getfloat() got EOF\n");
	else if (res == 0)
		printf("getfloat() got no number\n");
	else
		printf("something`s wrong in getfloat()\n");
	return 0;
}
