/**
 * Exercise 1-2, page 11
 * Упражнение 1.2, страница 22
 * 
 * Experiment to find out what happens when prints 's argument string contains
 * \c, where c is some character not listed above.
 *
 * Попытайтесь выяснить экспериментально, что происходит при передаче в функцию
 * printf строки, содержащей управляющую последовательность \c, где с - некий
 * символ, не входящий в вышеперечисленные комбинации.
 */

#include <stdio.h>

int main (void) {
	printf("new\nstring\ntest\n");
	printf("tab test\ttab test\n");
	printf("backspace test\bbackspace test\n");
	printf("backslash test \\ \n");

	printf("\nlist of escape sequences:\n");
	printf("alert			\\a	%d\n", '\a');
	printf("backspace   		\\b	%d\n", '\b');
	printf("horizont tab   		\\t	%d\n", '\t');
	printf("new line   		\\n	%d\n", '\n');
	printf("vertical tab   		\\v	%d\n", '\v');
	printf("formfeed   		\\f	%d\n", '\f');
	printf("carriage return   	\\r	%d\n", '\r');
	printf("double quote   		\\\"	%d\n", '\"');
	printf("single quote		\\\'	%d\n", '\'');
	printf("question mark		\\?	%d\n", '\?');
	printf("backslash   		\\\\	%d\n", '\\');

	printf("hex to decimal		\\x32	%d\n", '\x32');
	printf("octal to decimal	\\32	%d\n", '\32');

	printf("something undefined	\\d	%d\n", '\d');

	printf("\n");
	printf("Vertical tab \v is tricky, as its behaviour is unspecified under certain conditions.\n");
	printf("form feed. \f\n");
	printf("This escape, \r, moves the active position to the initial position of the current line.\n");
	printf("bell...\a\n");

	return 0;
}
