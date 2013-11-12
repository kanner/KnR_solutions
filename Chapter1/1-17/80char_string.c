/**
 * Exercise 1-17, page 31
 * Упражнение 1.17, страница 44
 * 
 * Write a program to print all input lines that are longer than 80 characters.
 *
 * Напишите программу для вывода всех строк входного потока, имеющих длину
 * более 80 символов.
 */

#include <stdio.h>
#define MINLENGTH	81

int my_getline(char line[], int maxline);

int main (void) {
	int c;
	int len = 0;
	char line[MINLENGTH];

	while ((len = my_getline(line, MINLENGTH)) > 0) {
		// we don`t need to consider '\n' on the end - just line length
		if ((len == MINLENGTH - 1) && line[len-1] != '\n') {
			printf ("this line is longer than 80 characters - %s", line);
			while ((c = getchar()) != EOF && c != '\n')
				putchar(c);
			putchar('\n');
		}
	}

	return 0;
}

int my_getline(char s[], int lim) {
	int c = 0;	// should be initialized
	int i;
	for (i=0; i < lim-1 && (c = getchar()) != EOF && c !='\n'; i++)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		i++;
	}
	s[i] = '\0';
	return i;
}
