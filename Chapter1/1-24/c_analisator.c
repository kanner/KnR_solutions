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

int main (void) {
	int c;
	/** we will check (), [], {}, '', "" */
	int num_parentheses = 0;
	int num_brackets = 0;
	int num_braces = 0;
	int num_quote_single = 1;	// 1 means that there`s even number of quotes
	int num_quote_double = 1;	// -1 means that there`s odd number of quotes

	while ((c = getchar()) != EOF) {
		if (c == '(')
			num_parentheses++;
		if (c == ')')
			num_parentheses--;
		if (c == '[')
			num_brackets++;
		if (c == ']')
			num_brackets--;
		if (c == '{')
			num_braces++;
		if (c == '}')
			num_braces--;
		if (c == '\'') {
			num_quote_single *= -1;
		}
		if (c == '\"')
			num_quote_double *= -1;
	}
// need to check if the symbols is in comments
// need to check previous \ symbol (escape)
	printf("\n");
	if (num_parentheses != 0)
		printf("there`s parentheses mismatch\n");
	else if (num_brackets != 0)
		printf("there`s brackets mismatch\n");
	else if (num_braces != 0)
		printf("there`s braces mismatch\n");
	else if (num_quote_single < 0)
		printf("there`s single quote mismatch\n");
	else if (num_quote_double < 0)
		printf("there`s double quote mismatch\n");
	else
		printf("C-syntax seems to be correct.\n");

	return 0;
}

