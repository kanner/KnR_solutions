/**
 * Exercise 1-9, page 21
 * Упражнение 1.9, страница 33
 * 
 * Write a program to copy its input to its output, replacing each string of one or
 * more blanks by a single blank.
 *
 * Напишите программу для копирования входного потока в выходной с заменой каждой
 * строки, состоящей из одного или нескольких пробелов, одним пробелом.
 */

#include <stdio.h>

int main (void) {
	int c;
	int blank_count = 0;

	printf("enter some words with double spaces between:\n");
	while ((c = getchar()) != EOF ) {
		if (c == ' ') {
			if (blank_count == 0) {
				blank_count = 1;
				putchar(c);
			}
		}
		else {
			blank_count = 0;
			putchar(c);
		}
	}
	return 0;
}
