/**
 * Exercise 5-19, page 104
 * Упражнение 5.19, страница 137
 *
 * Modify undcl so that it does not add redundant parentheses to declarations.
 *
 * Доработайте undcl так, чтобы программа не добавляла в объявления лишних
 * круглых скобок.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum {
	NAME,
	PARENS,
	BRACKETS
};

/** Ex. 4-4 */
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
	else
		buf[bufp++] = c;
}

/** last lexem type */
int tokentype;
/** last lexem */
char token[MAXTOKEN];
/** previous token (only one symbol needed) */
char prevtoken = '\0';
/** identifier name */
char name[MAXTOKEN];
/** char, int, etc */
char datatype[MAXTOKEN];
/** result string */
char out[1000];

/** get next token/lexem */
int gettoken(void) {
	int c, getch(void);
	void ungetch(int);
	char *p = token;

	/** skip whitespaces */
	while ((c = getch()) == ' ' || c == '\t')
		;

	/** collect '(' and "()" tokens */
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		else {
			ungetch(c);
			return tokentype = '(';
		}
	}
	/** collect "[SIZE]" tokens */
	else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	}
	/** collect "NAME" tokens */
	else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	}
	/** collect everything else */
	else
		return tokentype = c;
}

void dcl(void);
void dirdcl(void);

/** parse declaration (syntax analize) */
void dcl(void) {
	int ns;

	/** count stars */
	for (ns = 0; gettoken() == '*'; )
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

/** parse direct declaration */
void dirdcl(void) {
	int type;

	/** "( dcl )" */
	if (tokentype == '(') {
		dcl();
		if (tokentype != ')')
			printf("error: missing ')'\n");
	}
	/** variable name */
	else if (tokentype == NAME)
		strcpy(name, token);
	else
		printf("error: expected name or ( dcl )\n");

	while ((type = gettoken()) == PARENS || type == BRACKETS) {
		if (type == PARENS)
			strcat(out, " function returning");
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
}

int main (void) {
	int type;
	char temp[MAXTOKEN];

	while (gettoken() != EOF) {
		strcpy(out, token);
		while ((type = gettoken()) != '\n')
			if (type == PARENS || type == BRACKETS) {
				if (prevtoken == '*')
					sprintf(temp, "(%s) ", out);
				else
					sprintf(temp, "%s", out);
				strcat(temp, token);
				strcpy(out, temp);
//				strcat(out, token);
				prevtoken = '\0';
			}
			else if (type == '*') {
				sprintf(temp, "*%s", out);
//				sprintf(temp, "(*%s) ", out);
				strcpy(out, temp);
				prevtoken = '*';
			}
			else if (type == NAME) {
				if (prevtoken == '*')
					sprintf(temp, "%s (%s) ", token, out);
				else
					sprintf(temp, "%s %s", token, out);
//				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
				prevtoken = '\0';
			}
			else {
				if (prevtoken == '*')
					sprintf(temp, "(%s) ", out);
				else
					sprintf(temp, "%s", out);
				strcpy(out, temp);
				printf("invalid input at %s\n", token);
				prevtoken = '\0';
			}
		printf("%s\n", out);
	}
	return 0;
}
