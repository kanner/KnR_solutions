/*
 * Exercise 1-8, page 21
 * Упражнение 1.8, страница 33
 * 
 * Write a program to count blanks, tabs, and newlines.
 *
 * Напишите программу для подсчета пробелов, знаков табуляции и
 * символов конца строки.
 */

#include <stdio.h>

int main (void) {
	int c, newline_count, space_count, tabs_count;
	newline_count = space_count = tabs_count = 0;

	printf("enter some characters with EOF on the end\n");
	while ((c = getchar()) != EOF ) {
		if (c == '\n')
			newline_count++;
		if (c == '\t')
			tabs_count++;
		if (c == ' ')
			space_count++;
	}
	printf("newlines = %d\ntabs = %d\nspaces = %d\n", newline_count, tabs_count, space_count);

	return 0;
}
