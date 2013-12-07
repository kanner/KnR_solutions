/**
 * Exercise 1-23, page 34
 * Упражнение 1.23, страница 47
 * 
 * Write a program to remove all comments from a C program. Don't forget to
 * handle quoted strings and character constants properly. C comments don't nest.
 *
 * Напишите программу для удаления всех комментариев из программы на C.
 * Позаботьтесь о корректной обработке символьных констант и строк в двойных
 * кавычках. Вложенные комментарии в С не допускаются.
 */

#include <stdio.h>

#define CODE	0
#define COMMENT	1
#define SIMPLE_COMMENT	2
#define QUOTE	3
#define SLASH	4
#define STAR	5
#define LITERAL	6

int main(void)
{
	int c;
	/*
	 * we have several states:
	 *	- CODE/COMMENT/SIMPLE_COMMENT
	 *	- SLASH (one '/' inserted in CODE state)
	 *	- QUOTE ('"' or '\'' inserted in CODE state)
	 *	- STAR ('*' inserted in COMMENT state)
	 *	- LITERAL ('\\' inserted in QUOTE state - in string or char constant)
	 */
	int state;
	/** just to initialize */
	char quote = '\'';

	/** at first the state is CODE */
	state = CODE;
	while ((c = getchar()) != EOF) {
		if (state == CODE) {
			/** inserted one '/' in code (transition to state SLASH) */
			if (c == '/')
				state = SLASH;
			else {
				/** quotes inserted in code (transition to state QUOTE) */
				if (c == '"' || c == '\'') {
					state = QUOTE;
					quote = c;
				}
				/** put all characters in QUOTE and CODE states */
				putchar(c);
			}
		}
        else if (state == QUOTE) {
			/** inserted '\\' in QUOTE state (transition to state LITERAL) */
			if (c == '\\')
				state = LITERAL;
			/** we ended literal with the same quote-char (transition back to state CODE) */
			else if (c == quote)
				state = CODE;
			/** put all characters in QUOTE, LITERAL and CODE states */
			putchar(c);
		}
        else if (state == SLASH) {
			/** we started the comment with '/' and '*' (transition to state COMMENT) */
			if (c == '*')
				state = COMMENT;
			/** we started the comment with '/' and '/' (transition to state COMMENT) */
			else if (c == '/')
				state = SIMPLE_COMMENT;
			/** quotes inserted in code (transition to state QUOTE) */
			else if (c == '"' || c == '\'') {
				state = QUOTE;
				quote = c;
			}
			/** '/' could be just code character (transition to state CODE) */
			else {
				state = CODE;
				putchar('/');
				putchar(c);
			}
		}
		/** inserted '*' in COMMENT state (transition to state STAR) */
		else if (state == COMMENT) {
			if (c == '*')
				state = STAR;
		}
		/** the line end in '/' + '/' comment (transition to state CODE) */
		else if (state == SIMPLE_COMMENT) {
			if (c == '\n') {
				state = CODE;
				putchar(c);
			}
		}
		else if (state == STAR) {
			/** we ended comment with * and / (transition to state CODE) */
			if (c == '/')
				state = CODE;
			/** otherwise we are still in COMMENT state */
			else if (c != '*')
				state = COMMENT;
		}
	/** insert char and back to QUOTE state (transition to state QUOTES) */
        else if (state == LITERAL) {
			putchar(c);
			state = QUOTE;
		}
	}
	return 0;
}
