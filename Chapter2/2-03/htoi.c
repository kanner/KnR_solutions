/**
 * Exercise 2-3, page 43
 * Упражнение 2.3, страница 60
 * 
 * Write a function htoi(s), which converts a string of hexadecimal digits
 * (including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0
 * through 9, a through f, and A through F.
 *
 * Напишите функцию htoi(s), которая преобразует строку шестнадцатиричных цифр
 * (учитывая необязательные элементы 0x или 0X) в ее целочисленный эквивалент.
 * В число допустимых цифр входят десятичные цифры от 0 до 9, а также буквы
 * a-f и A-F.
 */

#include <stdio.h>

#define LENGTH	1000

int htoi(char *str) {
	int i, c, n;

	n = 0;
	for (i=0; (c = str[i]) != '\0'; ++i) {
		/** each digit from left to right must be multiplied by 16 */
		n *= 16;
		if (i == 0 && c == '0') {
			c = str[++i];
			/** if there`s 0x or 0X - skip it, otherwise return iterator to begining */
			if (c != 'x' && c != 'X')
				--i;
		}
		else if (c >= '0' && c <= '9')
			/** simple numeric */
			n += c - '0';
		else if (c >= 'a' && c <= 'f')
			/** letter in range 'a-f' */
			n += 10 + (c - 'a');
		else if (c >= 'A' && c <= 'F')
			/** letter in range 'A-F' */
			n += 10 + (c - 'A');
		else
			/** something wrong - return our value as it is */
			return n/16;
	}
	return n;
}

int main (void) {
	int i, c;
	char str[LENGTH] = {0};

	for (i = 0; (c = getchar()) != '\n' && i <= LENGTH - 1; i++)
		str[i] = c;
	str[i] = '\0';
	printf("hex string: \'%s\'\ndecimal string: \'%d\'\n", str, htoi(str));
	return 0;
}
