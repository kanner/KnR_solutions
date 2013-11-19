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

#define	CODE			0
#define	COMMENT			1
#define	SIMPLE_COMMENT	2
#define	QUOTE			3
#define SLASH			4
#define STAR			5
#define LITERAL			6

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
	char quote = '\'';	// just to initialize

	state = CODE;		// at first the state is CODE
	while ((c = getchar()) != EOF) {
		if (state == CODE) {
			if (c == '/')						// inserted one '/' in code (transition to state SLASH)
				state = SLASH;
			else {
				if (c == '"' || c == '\'') {	// quotes inserted in code (transition to state QUOTE)
					state = QUOTE;
					quote = c;
				}
				putchar(c);						// put all characters in QUOTE and CODE states
			}
		}
        else if (state == QUOTE) {
			if (c == '\\')						// inserted '\\' in QUOTE state (transition to state LITERAL)
				state = LITERAL;
			else if (c == quote)				// we ended literal with the same quote-char (transition back to state CODE)
				state = CODE;
			putchar(c);							// put all characters in QUOTE, LITERAL and CODE states
		}
        else if (state == SLASH) {
			if (c == '*')						// we started the comment with '/' and '*' (transition to state COMMENT) */
				state = COMMENT;
			else if (c == '/')					// we started the comment with '/' and '/' (transition to state COMMENT)
				state = SIMPLE_COMMENT;
			else if (c == '"' || c == '\'') {	// quotes inserted in code (transition to state QUOTE)
				state = QUOTE;
				quote = c;
			}
			else {								// '/' could be just code character (transition to state CODE)
				state = CODE;
				putchar('/');
				putchar(c);
			}
		}
		else if (state == COMMENT) {			// inserted '*' in COMMENT state (transition to state STAR)
			if (c == '*')
				state = STAR;
		}
		else if (state == SIMPLE_COMMENT) {		// the line end in '/' + '/' comment (transition to state CODE)
			if (c == '\n') {
				state = CODE;
				putchar(c);
			}
		}
		else if (state == STAR) {
			if (c == '/')						// we ended commet with */ (transition to state CODE)
				state = CODE;
			else if (c != '*')					// otherwise we are still in COMMENT state
				state = COMMENT;
		}
        else if (state == LITERAL) {			// insert char and back to QUOTE state (transition to state QUOTES)
			putchar(c);
			state = QUOTE;
		}
	}
	return 0;
}
