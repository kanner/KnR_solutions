/**
 * Exercise 1-18, page 31
 * Упражнение 1.18, страница 44
 * 
 * Write a program to remove trailing blanks and tabs from each line of input, and
 * to delete entirely blank lines.
 *
 * Напишите программу для удаления лишних пробелов и табуляций в хвосте каждой
 * поступающей строки входного потока, которая бы также удаляла полностью пустые строки.
 */

#include <stdio.h>

#define MAXLINE 1000

int my_getline(char line[], int maxline);

int main (void) {
	int len;
	char line[MAXLINE];
	int head, tail, inner;

	while ((len = my_getline(line, MAXLINE)) > 0) {
		/** first find out where`s the beginning of real text */
		for(head = 0; line[head] == ' ' || line[head] == '\t'; head++);
		/** second find out where`s the real end of the text */
		for(tail = len; line[tail] == ' ' || line[tail] == '\t' || line[tail] == '\n' || line[tail] == '\0'; tail--);
		if (tail - head >= 0) {
			/** from real beginning till real end - print chars */
			for(inner = head; inner <= tail; inner++)
				putchar(line[inner]);
			/** thats for example, in order to see the real EOF in output (actually before EOF) */
			printf("EOF");
			putchar('\n');
			putchar('\0');
		}
	}
	return 0;
}

int my_getline(char s[], int lim) {
	/** should be initialized */
	int c = 0;
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
