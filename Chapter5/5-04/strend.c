/**
 * Exercise 5-4, page 89
 * Упражнение 5.4, страница 118
 * 
 * Write the function strend(s,t), which returns 1 if the string t occurs at the
 * end of the string s, and zero otherwise.
 *
 * Напишите функцию strend(s,t), которая бы возвращала 1, если строка t
 * присутствует в конце строки s, и 0 в противном случае.
 */

#include <stdio.h>

int strend(char *s, char *t) {
	int length1, length2;

	/** find out length of two strings */
	for (length1 = 0; *(s + length1) != '\0'; ++length1)
		;
	for (length2 = 0; *(t + length2) != '\0'; ++length2)
		;

	if (length1 > length2) {
		/** find where second string should start */
		s += length1 - length2;
		while (*s++ == *t++)
			/** if it`s ok - there should be '\0' at the end */
			if (!*s)
				return 1;
	}
	return 0;
}

int main (void) {
	char str1[6] = "hello";
	char str2[4] = "lo";
	printf("strend result = \'%d\'\n", strend(str1, str2));
	return 0;
}
