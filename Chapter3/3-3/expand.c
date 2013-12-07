/**
 * Exercise 3-3, page 56
 * Упражнение 3.3, страница 77
 * 
 * Write a function expand(s1,s2) that expands shorthand notations like a-z in
 * the string s1 into the equivalent complete list abc...xyz in s2 . Allow for letters of either case
 * and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z . Arrange that a
 * leading or trailing - is taken literally.
 *
 * Напишите функцию expand(s1,s2), которая бы разворачивала сокращенную запись наподобие a-z в строке
 * s1 в полный список abc...xyz в строке s2. Учитывайте буквы в любом регистре, цифры, а также записи
 * вида a-b-c,a-z0-9 и -a-z. Сделайте так, чтобы знаки - в начале и в конце строки воспинимались
 * буквально, а не как символы развертывания
 */

#include <stdio.h>

#define MAX_LENGTH	100

int checkrange(char c1, char c2)
{
	/** valid range in a-z */
	if (('a' <= c1 && c1 <= 'z') && (c1 <= c2 && c2 <= 'z'))
		return 1;
	/** valid range in A-Z */
	if (('A' <= c1 && c1 <= 'Z') && (c1 <= c2 && c2 <= 'Z'))
		return 1;
	/** valid range in 0-9 */
	if (('0' <= c1 && c1 <= '9') && (c1 <= c2 && c2 <= '9'))
		return 1;
	/** not a valid range */
	return 0;
}

void expand(char *s1, char *s2) {
	int i, j;

	for (i = j = 0; s1[i] != '\0'; ++i) {
		if (s1[i] == '-') {
			if (i == 0 || s1[i+1] == '\0') {
				s2[j++] = s1[i];
			}
            else {
				if (checkrange(s1[i-1], s1[i+1])) {
					while (s2[j-1] < s1[i+1]) {
						s2[j] = s2[j-1] + 1;
						j++;
					}
					++i;
				}
				else
					s2[j++] = s1[i];
			}
		}
		else
			s2[j++] = s1[i];
	}
	s2[j] = '\0';
}

int main (void) {
	char str1[MAX_LENGTH] = "-a-b-cA-b some text 1-1 b-a";
	char str2[MAX_LENGTH];

	expand(str1,str2);
	printf("str1 = \'%s\'\n", str1);
	printf("str2 = \'%s\'\n", str2);
	return 0;
}
