/**
 * Exercise 4-13, page 74
 * Упражнение 4.13, страница 101
 * 
 * Write a recursive version of the function reverse(s) , which reverses the
 * string s in place.
 *
 * Напишите рекурсивную версию функции reverse(s), которая обращает порядок
 * символов в строке прямо на месте, без дополнительного строкового буфера.
 */

#include <stdio.h>
#include <string.h>

/**
 * this is the copy of reverse() from Ex.3.4
 */
void reverse (char s[]) {
	int i, j, c;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
		c = s[i], s[i] = s[j], s[j] = c;
}

void reverse_recursive (char s[]) {
	static int index;

	char c = s[index];
	s[index] = s[strlen(s) - 1 - index];
	s[strlen(s) - 1 - index] = c;
	index++;
	/** we should check two indexes - 'end' and 'beginning' */
	if (index < strlen(s)/2)
		reverse_recursive(s);
}

int main (void) {
	char str[6] = "hello";

	reverse_recursive(str);
	printf("reverse string is \'%s\'\n", str);
	return 0;
}
