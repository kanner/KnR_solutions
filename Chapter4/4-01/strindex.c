/**
 * Exercise 4-1, page 61
 * Упражнение 4.1, страница 84
 * 
 * Write the function strindex(s,t) which returns the position of the rightmost
 * occurrence of t in s, or -1 if there is none.
 *
 * Напишите функцию strrindex(s,t), которая бы возвращала индекс самого правого
 * вхождения строки t в s, либо -1, если такой строки s нет.
 */

#include <stdio.h>
#define MAXLINE	1000

char pattern[] = "test";

int strrindex (char *s, char *t) {
	int i, j, k;
	int rindex = -1;
	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			rindex = i;	
	}
	return rindex;
}

int strindex (char *s, char *t) {
	int i, j, k;

	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}

int _getline (char *s, int lim) {
	int c = '\0';
	int i;
	
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

int main (void) {
	int lim = MAXLINE;
	char line[MAXLINE] = {0}; //"I use test for testing";
	int found = 0;

	while (_getline(line, lim) > 0) {
		if (strindex(line, pattern) >= 0) {
			printf("%s %d, %d\n", line, strindex(line, pattern)+1, strrindex(line, pattern)+1);
			found++;
		}
	}
	return found;
}
