/**
 * Exercise 1-10, page 21
 * Упражнение 1.10, страница 33
 * 
 * Write a program to copy its input to its output, replacing each tab by \t , each
 * backspace by \b , and each backslash by \\ . This makes tabs and backspaces visible in an
 * unambiguous way.
 *
 * Напишите программу для копирования входного потока в выходной с заменой знаков табуляции
 * на \t, символов возврата назад (Backspace) на \b, а обратных косых черт - на \\. Это сделает
 * табуляции и символы возврата легко читаемыми в потоке.
 */

#include <stdio.h>

int main (void) {
	int c;
	printf("enter some words with tabs backspaces and \\ inside:\n");
	while ((c = getchar()) != EOF ) {
		if (c == '\\') {
			//printf("\\\\");
			putchar('\\');
			putchar('\\');
		}
		// on my system that didn`t work
		else if (c == '\b') {
			//printf("\\b");
			putchar('\\');
			putchar('b');
		}
		else if (c == '\t') {
			//printf("\\t");
			putchar('\\');
			putchar('t');
		}
		else
			//printf("%c", c);
			putchar(c);
	}
	return 0;
}
