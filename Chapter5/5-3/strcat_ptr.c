/**
 * Exercise 5-3, page 89
 * Упражнение 5.3, страница 118
 * 
 * Write a pointer version of the function strcat that we showed in Chapter 2:
 * strcat(s,t) copies the string t to the end of s.
 *
 * Напишите свою версию функции strcat, продемонстрированной в главе 2, с
 * применением указателей. Напоминаем, что strcat(s,t) копирует строку
 * t в конец строки s.
 */

#include <stdio.h>

void _strcat(char s[], char t[]) {
	int i, j;
	i = j = 0;

	while (s[i] != '\0')
		/** find end of s */
		i++;
	while ((s[i++] = t[j++]) != '\0')
		/** copy t */
		;
}

void _strcat_ptr(char *s, const char *t) {
	while(*s)
		/** find end of s */
		s++;
	while(*t)
		/** copy t */
		*s++ = *t++;
	*s = '\0';
}

int main (void) {
	char str1[7+7] = "hello ";
	char str2[7] = "world!";
	_strcat_ptr(str1, str2);
	printf("string = \'%s\'\n", str1);
	return 0;
}
