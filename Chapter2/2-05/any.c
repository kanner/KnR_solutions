/**
 * Exercise 2-5, page 45
 * Упражнение 2.5, страница 62
 * 
 * Write the function any(s1,s2), which returns the first location in a string s1
 * where any character from the string s2 occurs, or -1 if s1 contains no characters from s2.
 * (The standard library function strpbrk does the same job but returns a pointer to the
 * location.)
 *
 * Напишите функцию any(s1,s2), возвращающую номер первой позиции в строке s1, в которой
 * находится какой-либо из символов строки s2, либо -1, если строка s1 не содержит ниодного
 * символа из s2. (Стандартная библиотечная функция strpbrk делает то же самое, но возвращает
 * указатель на найденную позицию.)
 */

#include <stdio.h>

int any(char *str1, char *str2) {
	int i, k;

	for (i = 0; str1[i] != '\0'; i++) {
		for (k = 0; str2[k] != '\0'; k++) {
			if (str1[i] == str2[k]) {
				return i+1;
			}
		}
	}
	return -1;
}

int main (void) {
	int res = 0;
	char str[8] = "testing";
	char _str[15] = "zzzzzzzzzzzer";

	res = any(str, _str);
	if (res == -1)
		printf("There`s no symbols from \'%s\' in string \'%s\'", _str, str);
	else
		printf("The first occurrence of symbols from \'%s\' in string \'%s\' is in %d symbol\n", _str, str, res);
	return 0;
}
