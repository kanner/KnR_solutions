/**
 * Exercise 5-18, page 104
 * Упражнение 5.18, страница 137
 *
 * Make dcl recover from input errors.
 *
 * Доработайте dcl так, чтобы программа справлялась с обработкой ошибок
 * во входных данных.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/** assume possible errors are:
 * 1. no type identifier at first position
 * 2. unmatched (unclosed) parens or brackets
 * 3. error symbols like '{', '}', ';', '=' and ','
 * 4. function parameters (see 5-20)
 * 5. some wrong space symbols
 */

/** you can alter this values and all shoul keep working */
char errsym[] = {
	'{',
	'}',
	';',
	'=',
	',',
	'\0' // used only like EOM (END OF MASSIVE)
};

/** return 1 if error symbol entered, else -- return 0 */
int check_errsym(char symbol)
{
	int i = 0;
	int found = 0;

	while (errsym[i] != '\0')
		if (errsym[i++] == symbol)
			found = 1;
	if (found)
		return 1;
	return 0;
}

#define MAXTOKEN 100

enum {
	NAME,
	PARENS,
	BRACKETS,
	ERR
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
		for (*p++ = c; (*p = getch()) != ']'; p++) {
			/** check if there are num or symbol in [] */
			if (!(isalnum(*p))) {
				*(++p) = '\0';
				return tokentype = ERR;
			}

			/** 3. return on error symbol */
			if (check_errsym(*p)) {
				*(++p) = '\0';
				return tokentype = ERR;
			}
		}
		*(++p) = '\0';
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
	/** 3. check for error symbol */
	else if (check_errsym(c))
		return tokentype = ERR;
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

	/** 3. check last called gettoken() results */
	if (tokentype == ERR) {
		printf("error[2]: some error symbol inserted\n");
		return;
	}

	dirdcl();

	/** 3. check dirdcl() results (assume error message already printed) */
	if (tokentype == ERR)
		return;

	while (ns-- > 0)
		strcat(out, " pointer to");
}

/** parse direct declaration */
void dirdcl(void) {
	int type;

	/** assume here: tokentype != ERR before we call gettoken() */

	/** "( dcl )" */
	if (tokentype == '(') {
		dcl();
		if (tokentype != ')') {
			printf("error: missing ')'\n");
			tokentype = ERR;
			return;
		}
	}
	/** variable name */
	else if (tokentype == NAME)
		strcpy(name, token);
	else {
		printf("error: expected name or ( dcl )\n");
		tokentype = ERR;
		return;
	}

	while ((type = gettoken()) == PARENS || type == BRACKETS) {
		if (type == PARENS)
			strcat(out, " function returning");
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}

	/** 3. one more check for ERR after gettoken() */
	if (type == ERR) {
		printf("error[3]: some error symbol inserted\n");
		return;
	}
}

int main (void) {
	int got_type = 0;

	/** first lexem in string */
	while (gettoken() != EOF) {
		/** 3. process error characters */
		if (tokentype == ERR) {
			printf("error[1]: some error symbol inserted\n");
			return -1;
		}

		/** 1. added check for empty first (datatype) value */
		if ((got_type == 0) && tokentype != NAME) {
			printf("error: return type needed at first position\n");
			return -1;
		}
		else {
			/** lexem type */
			strcpy(datatype, token);
			got_type = 1;
		}

		out[0] = '\0';
		/** process rest of line */
		dcl();
		if (tokentype != '\n') {
			printf("syntax error in/after '%s'-token\n", token);
			return -1;
		}
		printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}
