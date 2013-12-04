/**
 * Exercise 2-10, page 48
 * Упражнение 2.10, страница 66
 * 
 * Rewrite the function lower , which converts upper case letters to lower case,
 * with a conditional expression instead of if-else .
 *
 * Перепишите функцию lower, которая преобразует буквы в верхнем регистре к
 * нижнему, с использованием условного выражения вместо конструкции if-else.
 */

#include <stdio.h>

int lower(int c) {
	return ('A' <= c && c <= 'Z') ? c - 'A' + 'a' : c;
}

int main (void) {
	printf("%c\n", lower('A'));
	return 0;
}
