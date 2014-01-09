/**
 * Exercise 5-5, page 89
 * Упражнение 5.5, страница 118
 * 
 * Write versions of the library functions strncpy, strncat, and strncmp, which
 * operate on at most the first n characters of their argument strings. For example,
 * strncpy(s,t,n) copies at most n characters of t to s. Full descriptions are in Appendix B.
 *
 * Применяя указатели, напишите ваши версии библиотечных функций strncpy, strncat и strncmp,
 * которые обрабатывают не более чем n первых символов своих строковых аргументов. Например,
 * функция strncpy(s,t,n) копирует не более n символов из строки t в строку s.
 */

#include <stdio.h>

void _strncpy(char *s, char *t, int n) {
	int i = 0;
	while((*s++ = *t++) != '\0' && ++i < n)
		;
}

void _strcpy(char *s, char *t) {
	while((*s++ = *t++) != '\0')
		;
}

void _strncat(char *s, const char *t, int n) {
	int i = 0;
	while(*s)
		/** find end of s */
		s++;
	while(*t && i++ < n)
		/** copy t */
		*s++ = *t++;
	*s = '\0';
}

void _strcat(char *s, const char *t) {
	while(*s)
		/** find end of s */
		s++;
	while(*t)
		/** copy t */
		*s++ = *t++;
	*s = '\0';
}

int _strncmp(char *s, char *t, int n) {
	int i = 0;
	for ( ; *s == *t && ++i < n; s++, t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
}

int _strcmp(char *s, char *t) {
	for ( ; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
}

int main (void) {
	char str1[6] = "hello";
	char str2[6] = "world";
	char str3[12] = "hello ";
	_strncpy(str1, str2, 4);
	printf("strncpy() result = \'%s\', \'%s\'\n", str1, str2);
	printf("strncmp() positive result = %d\n", _strncmp("12354", "12345", 3));
	printf("strncmp() non-positive result = %d\n", _strncmp("12354", "12345", 4));
	_strncat(str3, str2, 4);
	printf("strncat() result = \'%s\'\n", str3);
	return 0;
}
