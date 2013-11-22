/**
 * Exercise 1-24, page 34
 * Упражнение 1.24, страница 47
 * 
 * Write a program to check a C program for rudimentary syntax errors like
 * unmatched parentheses, brackets and braces. Don't forget about quotes, both single and
 * double, escape sequences, and comments. (This program is hard if you do it in full generality.)
 *
 * Напишите программу для выполнения примитивной синтаксической проверки программ на С, таких как
 * непарные круглые, квадратные и фигурные скобки. Не забудьте об одинарных и двойных кавычках,
 * управляющих символах и комментариях. (Это сложная программа, если пытаться реализовать самый
 * общий случай.)
 */

#include <stdio.h>

#define	CODE			0
#define	COMMENT			1
#define	SIMPLE_COMMENT	2
#define	QUOTE			3
#define SLASH			4
#define STAR			5
#define LITERAL			6

/** variables for comment_seek() */
int state;
char quote = '\'';	// just to initialize

#define	is_code	(state == CODE || state == QUOTE || state == SLASH)

/** Ex. 1-23 code without putchar()`s */
void comment_seek(int c) {
	if (state == CODE) {
		if (c == '/')						// inserted one '/' in code (transition to state SLASH)
			state = SLASH;
		else {
			if (c == '"' || c == '\'') {	// quotes inserted in code (transition to state QUOTE)
				state = QUOTE;
				quote = c;
			}
//			putchar(c);						// put all characters in QUOTE and CODE states
		}
	}
	else if (state == QUOTE) {
		if (c == '\\')						// inserted '\\' in QUOTE state (transition to state LITERAL)
			state = LITERAL;
		else if (c == quote)				// we ended literal with the same quote-char (transition back to state CODE)
			state = CODE;
//		putchar(c);							// put all characters in QUOTE, LITERAL and CODE states
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
//			putchar('/');
//			putchar(c);
		}
	}
	else if (state == COMMENT) {			// inserted '*' in COMMENT state (transition to state STAR)
		if (c == '*')
			state = STAR;
	}
	else if (state == SIMPLE_COMMENT) {		// the line end in '/' + '/' comment (transition to state CODE)
		if (c == '\n') {
			state = CODE;
//			putchar(c);
		}
	}
	else if (state == STAR) {
		if (c == '/')						// we ended commet with */ (transition to state CODE)
			state = CODE;
		else if (c != '*')					// otherwise we are still in COMMENT state
			state = COMMENT;
	}
	else if (state == LITERAL) {			// insert char and back to QUOTE state (transition to state QUOTES)
//		putchar(c);
		state = QUOTE;
	}
}

int main (void) {
	int c;
	/** we will check (), [], {}, '', "" */
	int num_parentheses = 0;
	int num_brackets = 0;
	int num_braces = 0;
	int num_quote_single = 1;	// 1 means that there`s even number of quotes
	int num_quote_double = 1;	// -1 means that there`s odd number of quotes

	while ((c = getchar()) != EOF) {
		comment_seek(c);
		if (c == '(' && is_code)
			num_parentheses++;
		if (c == ')' && is_code)
			num_parentheses--;
		if (c == '[' && is_code)
			num_brackets++;
		if (c == ']' && is_code)
			num_brackets--;
		if (c == '{' && is_code)
			num_braces++;
		if (c == '}' && is_code)
			num_braces--;
		if (c == '\'' && is_code)
			num_quote_single *= -1;
		if (c == '\"' && is_code)
			num_quote_double *= -1;
	}

	printf("\n");
	if (num_parentheses != 0)
		printf("C-syntax error: there`s parentheses mismatch\t['(' and ')']\n");
	if (num_brackets != 0)
		printf("C-syntax error: there`s brackets mismatch\t['[' and ']']\n");
	if (num_braces != 0)
		printf("C-syntax error: there`s braces mismatch\t\t['{' and '}']\n");
	if (num_quote_single < 0)
		printf("C-syntax error: there`s single quote mismatch\t['\'']\n");
	if (num_quote_double < 0)
		printf("C-syntax error: there`s double quote mismatch\t['\"']\n");
	if (num_parentheses == 0 && num_brackets == 0 && num_braces == 0 && num_quote_single > 0 && num_quote_double > 0)
		printf("C-syntax seems to be correct.\n");

	return 0;
}

