/**
 * Exercise 5-20, page 104
 * Упражнение 5.20, страница 137
 *
 * Expand dcl to handle declarations with function argument types, qualifiers like
 * const, and so on.
 *
 * Усовершенствуйте dcl так, чтобы программа обрабатывала объявления с типами
 * аргументов функций, модификаторами наподобие const и т.п.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/** assume possible additions for dcl are:
 * 1. complex types (const int, etc)
 * 1`. NAME not in types[]
 * 2. "struct" type (just add to types[]?)
 * 3. multi-arrays like "test[][]" (not processed)
 * 4. function parameters/arguments types
 * 5. type conversions? (not processed)
 */

/** lists of possible type- and variable modifiers */
char *types[] = {
	"char",
	"int",
	"float",
	"double",
	"short",	// like "short int"
	"long",		// like "long int"
	"short int",
	"long int",
	"long long",	// not in KnR
	"long double",
	"signed",	// not in KnR
	"unsigned",	// not in KnR
	"signed int",
	"unsigned int",
	"signed char",
	"unsigned char",
	"struct",
	/** add some more */
	"\0",
};

/** modifiers with space at the end */
char *type_modifiers[] = {
	"static",
	"const",
	"register", /*
		     * only for automatic variables and function parameters,
		     * could not be taken address of...
		     * we would not check all this!
		     */
	"\0"
};

/** return 1 if error occured (not correct type), else -- return 0 */
int check_type(char *str)
{
	int i, j;
	int found = 0;

	i = j = 0;
	/** 1. check in type_modifiers[] */
	while (strcmp(type_modifiers[i], "\0") != 0) {
		int len = strlen(type_modifiers[i]);
		if (strncmp(type_modifiers[i], str, len) == 0) {
			str = str + len + 1;
			found = 1;
			goto type_check;
		}
		i++;
	}

type_check:
	/** process blank symbols before type */
	while (str[0] == ' ')
		str = str + 1;
	/** 2. check in types[] */
	while (strcmp(types[j], "\0") != 0) {
		if (strcmp(types[j], str) == 0)
			goto found;
		j++;
	}
	/** found only modifier */
	if (found == 1)
		return -1;
	return 1;
found:
	return 0;
}

/** Ex. 5-18 */
/** you can alter this values and all shoul keep working */
char errsym[] = {
	'{',
	'}',
	';',
	'=',
	/** lets keep it to use in function`s arguments type */
//	',',
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
	DATATYPE,
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

/** we should return string to 'stdin' if something is wrong */
void ungetstr(char *str)
{
	int i = strlen(str);
	/** ungetch() in reverse order */
	while (i > 0) {
		ungetch(str[i-1]);
		i--;
	}
}

/** last lexem type */
int tokentype;
/** last lexem */
char token[MAXTOKEN];
/** temporary lexem */
char token_tmp[MAXTOKEN];
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
/*	else if (c == ')') {
		ungetch(c);
		return tokentype = ')';
	}
*/
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
	char c;

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
	else if (tokentype == NAME) {
		if (check_type(token) == 1)
			strcpy(name, token);
		else {
			printf("error: name should not be the same as type or type modifier.\n");
			tokentype = ERR;
			return;
		}
	}
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
	if (type == '(' && gettoken() == NAME && check_type(token)==0) {
		token_tmp[0] = '\0';
		strcat(token_tmp, " function (");
		strcat(token_tmp, token);
		while((c = gettoken()) == ',' && gettoken() == NAME && check_type(token)==0) {
			strcat(token_tmp, ",");
			strcat(token_tmp, token);
		}
		if (c == ')') {
			strcat(token_tmp, ") returning");
		}
		else {
			printf("error: something wrong with function`s argument types\n");
			ungetstr(token_tmp);
			return;
		}
		strcat(out, token_tmp);
		/** we should call this to go to next token */
		gettoken();
	}
	/** 3. one more check for ERR after gettoken() */
	else if (type == ERR) {
		printf("error[3]: some error symbol inserted\n");
		return;
	}
}

/**
 * We should populate token for some types (const modifiers, etc)
 *
 * This function got really complex because of using gettoken() from original
 * KnR code (which do different things on different tokens). It would be best
 * to rewrite gettoken() or use correct another one, which
 * ungetch()/ungetstr() non-DATATYPE/NAME tokens
 *
 */
int gettokentype(void) {
	char c;
	int modifier = 0;
	int type = 0;

	/** check last token correctness (allow modifiers) */
	if (check_type(token) == 1) {
		return tokentype = NAME;
	}
	else if (check_type(token) == -1) {
		modifier = 1;
		/** save last token value */
		strcpy(token_tmp, token);
	}
	else if (check_type(token) == 0) {
		type = 1;
		/** continue to process more complex type */
		strcpy(token_tmp, token);
	}

	token[0]='\0';
	while ((c = gettoken()) != EOF) {
		/** check new token first */
		if (tokentype == NAME && check_type(token) == 0) {
			/** concatenate */
			if (type == 1 || modifier == 1) {
				strcat(token_tmp, " ");
			}
			else {
				token_tmp[0] = '\0';
			}
			strcat(token_tmp, token);

			/** check complex token second */
			if (check_type(token_tmp) == 0) {
				// continue
				type = 1;
			}
			else {
				/** ungetch last token */
				ungetstr(token);
				token_tmp[strlen(token_tmp)-strlen(token)]='\0';
//				strcpy(token, token_tmp);
				goto out;
			}
		}
		else if (tokentype == NAME && check_type(token) != 0) {
			ungetstr(token);
			goto out;
/*			if (modifier == 1 && type == 0) {
//				return tokentype = ERR;
				goto out;
			}
			else if (type == 1) {
				ungetstr(token);
//				strcpy(token, token_tmp);
				goto out;
			}
			else
				return tokentype=NAME;
*/
		}
		else if (tokentype == PARENS || tokentype == BRACKETS) {
			ungetstr(token);
			goto out;
		}
		else if (tokentype == '(') {
			ungetch(tokentype);
			goto out;
		}
		else if (tokentype == ERR) {
			/** ungetch()/ungetstr() depends on ERR case... */
			ungetstr(token);
			goto out;
		}
		else {
			ungetch(c);
			goto out;
		}
	}
out:
	if (type == 1) {
		strcpy(token, token_tmp);
		return tokentype = DATATYPE;
	}
	else
		return tokentype = ERR;
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

		if (got_type == 0) {
			if (tokentype != NAME || gettokentype() != DATATYPE) {
				printf("error: return type needed at first position\n");
				return -1;
			}
			strcpy(datatype, token);
			got_type = 1;
		}

		/** 1. added check for empty first (datatype) value */
//		if ((got_type == 0) && tokentype != NAME) {
//			printf("error: return type needed at first position\n");
//			return -1;
//		}
//		else {
//                        /** lexem type */
//			strcpy(datatype, token);
//			got_type = 1;
//		}

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
