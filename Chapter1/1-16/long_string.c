/*
 * Exercise 1-16, page 31
 * Упражнение 1.16, страница 43
 * 
 * Revise the main routine of the longest-line program so it will correctly print the
 * length of arbitrary long input lines, and as much as possible of the text.
 *
 * Доработайте главный модуль программы определения самой длинной строки так,
 * чтобы она выводила правильное значение для какой угодно длины строк входного
 * потока, насколько это позволяет текст.
 */

#include <stdio.h>

#define MAXLINE	10

int my_getline(char line[], int maxline);	// getline was renamed because there is function with the same name in stdio
void copy(char to[], char from[]);

int main (void) {
	int c;
	int len, max;
	char line[MAXLINE];
	char longest[MAXLINE];

	max = 0;
	while ((len = my_getline(line, MAXLINE)) > 0) {
		/** added just this if-block to increment len till line end */
		if (line[len-1] != '\n')
			while ((c = getchar()) != EOF && c != '\n')
				++len;
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	}
	if (max > 0) {
		printf("longest line is %d characters\n", max);	// print length
		printf("content - '%s'\n", longest);
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

void copy(char to[], char from[]) {
	int i;
	i = 0;
	while ((to[i] = from[i]) != '\0')
		i++;
}
