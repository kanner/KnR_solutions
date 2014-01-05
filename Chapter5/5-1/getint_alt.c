/**
 * Exercise 5-1, page 81
 * Упражнение 5.1, страница 109
 * 
 * As written, getint treats a + or - not followed by a digit as a valid
 * representation of zero. Fix it to push such a character back on the input.
 *
 * Функция getint в ее нынешнем виде воспринимает плюс или минус без последующей
 * цифры как разрешенное представление нуля. Измените функцию так, чтобы она
 * возвращала символ назад в поток.
 */

#include <stdio.h>
#include <ctype.h>

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

int getint(int *pn) {
	int c, sign;
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
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

int main (void) {
	int x, res;

	res = getint(&x);
	if (res > 0)
		printf("getint() got int: %d\n", x);
	else if (res == EOF)
		printf("getint() got EOF\n");
	else if (res == 0)
		printf("getint() got no number\n");
	else
		printf("something`s wrong in getint()\n");
	return 0;
}
