/**
 * Exercise 5-6, page 89
 * Упражнение 5.6, страница 118
 * 
 * Rewrite appropriate programs from earlier chapters and exercises with pointers
 * instead of array indexing. Good possibilities include getline (Chapters 1 and 4), atoi, itoa,
 * and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop
 * (Chapter 4).
 *
 * Перепишите программы из примеров и упражнений предыдущих глав, применяя указатели
 * вместо индексов массивов. В частности, полезно будет поработать с такими функциями,
 * как getline (главы 1 и 4), atoi, itoa и их версиями (главы 2-4), reverse (глава 3),
 * а также strindex и getop (глава 4).
 */

#include <stdio.h>

/** ptr_getline() */
int _getline_ptr(char *s, int lim) {
	char c;
	char *p = s;
	
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	*s = '\0';
	return s - p;
}

/** ptr_atoi(), ptr_itoa(), reverse() */
#include <string.h>
#include <stdlib.h>
void reverse_ptr(char *s) {
	char *p = s + strlen(s) - 1;
	while (p > s) {
		char tmp = *s;
		*s++ = *p;
		*p-- = tmp;
	}

}

void itoa_alt_ptr(int n, char *s) {
	int sign = n;
	char *p = s;

	/** we can use absolute values to correct the problem */
	do {
		*p++ = abs (n % 10) + '0';
	} while ((abs(n /= 10)) > 0);
	if (sign < 0)
		*p++ = '-';
	*p = '\0';
	reverse_ptr(s);
}

void itoa_recursive_ptr(int n, char *s) {
	static char *p;

	if (n < 0) {
//		putchar('-');
		*s++ = '-';
//		n = -n;	// we can`t do it with INT_MIN
	}

	p = s;
	if (abs(n / 10))
		itoa_recursive_ptr(abs(n / 10), s);

//	putchar(abs (n % 10) + '0');
	*p++ = abs (n % 10) + '0';
	*p = '\0';
}

#include <ctype.h>
int atoi_ptr(const char *s)
{
	int n, sign;

	while (isspace(*s))
		/** skip whitespace */
		s++;
	sign = (*s == '-') ? -1 : 1;
	/** skip sign */
	if (*s == '+' || *s == '-')
		s++;
	for (n = 0; isdigit(*s); s++)
		n = 10 * n + (*s -'0');
	return sign * n;
}

/** ptr_strindex() */
int strindex_ptr(char *s, char *t) {
	const char *i, *j, *k;

	for (i = s; *i != '\0'; i++) {
		j = i;
		k = t;
		while (*k != '\0' && *j++ == *k++)
			;
		if (k-t > 0 && *k == '\0')
			return i - s;
	}
	return -1;
}

/** ptr_getop() */

/** signal that a number was found */
#define NUMBER '0'
/** signal that some function was found */
#define FUNCTION_OR_VARIABLE '1'
/** signal that '\0' was found */
#define ENDSTRING '2'
/** size of buffer for getch/ungetch */
#define BUFSIZE 100

/** buffer for ungetch */
char buf[BUFSIZE];
/** next free position in buf */
int  bufp = 0;

/** get a (pos1sibly pushed back) character */
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

int getop_ptr(char *s) {
	int c, next_ch;
	
	/** skip space symbpols */
	while ((*s = c = getch()) == ' ' || c == '\t')
		;
	*++s = '\0';

	if (isalpha(c)) {
		while (isalpha(*++s = c = getch()))
			;
		*s = '\0';
		if (c != EOF)
			ungetch(c);
		return FUNCTION_OR_VARIABLE;
	}

	if (!isdigit(c) && c != '.' && c != '-') {
		/** assigning a variable */
		if (c == '=' && (next_ch = getch()) == '\n') {
			ungetch('\0');
			return c;
		}
		if (c == '\0')
			return ENDSTRING;
		/** not number */
		return c;
	}

	/** check if there`s a number or '.' after '-' */
	if (c == '-') {
		next_ch = getch();
		if (!isdigit(next_ch) && next_ch != '.')
			return c;
		c = next_ch;
	}
	else
		c = getch();

	/** collect integer */
	while (isdigit(*++s = c))
		c = getch();
	if (c == '.')
		/** collect fraction */
		while (isdigit(*++s = c = getch()))
			;
	*s = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

#include <limits.h>
#define MAXLINE 1000
int main (void) {
	char line[MAXLINE] = {0};
	char string1[100] = {0};
	char string2[100] = {0};

	_getline_ptr(line, MAXLINE);
	printf("getline_ptr() result is:\n%s\n", line);

	itoa_alt_ptr(INT_MIN, string1);
	printf("itoa_alt_ptr() result for \'-2147483648\' (INT_MIN) is %s\n", string1);

	itoa_recursive_ptr(INT_MIN, string2);
	printf("itoa_recursive_ptr() result for \'-2147483648\' (INT_MIN) is %s\n", string2);

	printf("atoi_ptr() result for \'-2147483648\' (INT_MIN) is %d\n", INT_MIN);
	printf("strindex_ptr() result for \'world\' in \'hello world\' is %d\n", strindex_ptr("hello world", "world") + 1);
	return 0;
}
