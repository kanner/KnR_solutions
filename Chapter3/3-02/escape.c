/**
 * Exercise 3-2, page 53
 * Упражнение 3.2, страница 73
 * 
 * Write a function escape(s,t) that converts characters like newline and tab into
 * visible escape sequences like \n and \t as it copies the string t to s. Use a switch. Write a
 * function for the other direction as well, converting escape sequences into the real characters.
 *
 * Напишите функцию под именем escape(s,t), которая бы преобразовывала символы наподобие конца
 * строки и табуляции в управляющие последовательности языка C, такие как \n и \t, в процессе
 * копирования строки t в строку s. Воспользуйтесь оператором switch. Напишите функцию также
 * и для противоположной операции - преобразования символических управляющих последовательностей
 * в фактические управляющие символы.
 */

#include <stdio.h>

#define MAX_LENGTH	100

void escape(char *s, char *t) {
	int i,j = 0;
	/** here and later we need j to be less then MAX_LENGTH */
	for(i = 0; t[i] != '\0' && j <= MAX_LENGTH-3; i++) {
		switch(t[i]) {
			case '\n':
				s[j++] = '\\';
				s[j++] = 'n';
				break;
			case '\t':
				s[j++] = '\\';
				s[j++] = 't';
				break;
			default:
				s[j++] = t[i];
				break;
		}
	}
	s[j] = '\0';
	return;
}

void unescape(char *s, char *t) {
	int i, j = 0;
	int escape = 0;

	for(i = 0; t[i] != '\0'; i++) {
		switch(t[i]) {
			case '\\':
				escape = 1;
				break;
//			case ' ':
//				escape = 0;
//				break;
			case 'n':
				if (escape == 1) {
					s[j++] = '\n';
					escape = 0;
					break;
				}
				/** otherwise it`ll go to default */
			case 't':
				if (escape == 1) {
					s[j++] = '\t';
					escape = 0;
					break;
				}
				/** otherwise it`ll go to default: */
			default:
				s[j++] = t[i];
				/** we don`t need seeking other escape char`s */
				if(escape == 1)
					escape = 0;
				break;
		}
	}
	s[j] = '\0';
	return;
}

int main (void) {
	int i = 0;
	int c;
	char str1[MAX_LENGTH];
	char str2[MAX_LENGTH];

	while ((c = getchar()) != EOF && i < MAX_LENGTH)
		str2[i++] = c;
	str2[i] = '\0';

	printf("\n\nstr2 = \'%s\'\n", str2);
	escape(str1, str2);
	printf("str1 = \'%s\'\n", str1);
	unescape(str2, str1);
	printf("str2 = \'%s\'\n", str2);

	return 0;
}
