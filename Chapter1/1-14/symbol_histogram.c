/**
 * Exercise 1-14, page 25
 * Упражнение 1.14, страница 37
 * 
 * Write a program to print a histogram of the frequencies of different characters
 * in its input.
 *
 * Напишите программу для вывода гистограммы частот, с которыми встречаются во входном потоке
 * различные символы.
 */

#include <stdio.h>
/** for values of CHAR_MIN and CHAR_MAX */
#include <limits.h>

int main (void)
{
	int c, i, j;
	int chars[CHAR_MAX - CHAR_MIN + 1]={0};
	c = i = j = 0;

	while ((c = getchar()) != EOF)
		chars[c]++;

	for (i = 0; i <= CHAR_MAX - CHAR_MIN; i++) {
		if (chars[i] > 0) {
			if (i == '\b')
				printf(" \\b");
			else if (i == '\n')
				printf(" \\n");
			else if (i == '\t')
				printf(" \\t");
			else if (i == ' ')
				printf("' '");
			else
				printf("%3c", i);

			printf(" [%3d] : %3d\t", i, chars[i]);
			for (j = 1; j <= chars[i]; j++)
				printf("+");
			printf("\n");
		}
	}

	return 0;
}
