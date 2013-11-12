/**
 * Exercise 1-19, page 31
 * Упражнение 1.19, страница 44
 * 
 * Write a function reverse(s) that reverses the character string s . Use it to
 * write a program that reverses its input a line at a time.
 *
 * Напишите функцию reverse(s), которая переписывает свой строковый аргумент s
 * в обратном порядке. Воспользуйтесь ею для написания программы, которая бы
 * выполняла такое обращение над каждой строкой входного потока по очереди.
 */

#include <stdio.h>

#define MAXLINE 1000

int my_getline(char line[], int maxline);
void reverse(char line[], int len);

int main (void) {
	int len;
	char line[MAXLINE];

	while ((len = my_getline(line, MAXLINE)) > 0) {
		reverse(line, len);
		printf("%s", line);
	}
	return 0;
}

int my_getline (char s[], int lim) {
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

void reverse (char line[], int len) {
	int i;
	int _len = len;
	char temp;

	// let`s keep \n at the end of line
	if (line[_len - 1] == '\n')
		_len = _len - 1;

	for (i = 0; i < _len; ++i) {
		// let`s change [i] and [_len - 1] chars and decrease _len
		temp = line[i];
		line[i] = line[_len - 1];
		line[_len - 1] = temp;
		_len--;
	}
	return;
}

