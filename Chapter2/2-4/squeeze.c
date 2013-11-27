/**
 * Exercise 2-4, page 44
 * Упражнение 2.4, страница 62
 * 
 * Write an alternative version of squeeze(s1,s2) that deletes each character in
 * s1 that matches any character in the string s2.
 *
 * Напишите альтернативную версию функции squeeze(s1,s2), которая бы удаляла из
 * строки s1 все символы, встречающиеся в строке s2.
 */

#include <stdio.h>

void squeeze_orig(char *s, int c) {
	int i, j;
	for (i = j = 0; s[i] != '\0'; i++)
		if (s[i] != c)
			s[j++] = s[i];
	s[j] = '\0';
}

void squeeze_alt(char *str1, char *str2) {
	int i, j, k;
	int found;

	for (i = j = 0; str1[i] != '\0'; i++) {
		found = 0;
		for (k = 0; str2[k] != '\0' && found != 1; k++) {
			if (str1[i] == str2[k]) {
				found = 1;
			}
		}
		if (found == 0)
			str1[j++] = str1[i];
	}
	str1[j] = '\0';
}

int main (void) {
	char str[8] = "testing";
	char _str[15] = "tetttttttttsi";
//	int c = 't';

//	squeeze_orig(str, c);
	squeeze_alt(str, _str);
	printf("string after squeezing - \'%s\'\n", str);
	return 0;
}
