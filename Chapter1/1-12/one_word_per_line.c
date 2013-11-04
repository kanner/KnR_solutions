/*
 * Exercise 1-12, page 23
 * Упражнение 1.12, страница 35
 * 
 * Write a program that prints its input one word per line.
 *
 * Напишите программу для вывода входного потока по одному слову в строке
 */

#include <stdio.h>

int main (void) {
	int c;
	int blank = 0;
	printf("enter some words:\n");
	while ((c = getchar()) != EOF ) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (blank == 0)
				putchar('\n');
			blank = 1;
		}
		else {
			blank = 0;
			putchar(c);
		}
	}
	return 0;
}
