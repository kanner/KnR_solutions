/**
 * Exercise 1-22, page 34
 * Упражнение 1.22, страница 47
 * 
 * Write a program to ``fold'' long input lines into two or more shorter lines after
 * the last non-blank character that occurs before the n-th column of input. Make sure your
 * program does something intelligent with very long lines, and if there are no blanks or tabs
 * before the specified column.
 *
 * Напишите программу для сворачивания слишком длинных строк входного потока в две или более
 * коротких строки после последнего непустого символа, встречающегося перед n-м столбцом
 * длинной строки. Постарайтесь, чтобы ваша программа обрабатывала очень длинные строки
 * корректно, а также удаляла лишние пробелы и табуляции перед указанным столбцом.
 */

#include <stdio.h>

#define	TAB_WIDTH	4
#define	STR_WIDTH	80

int check_vowel(char ch) {
	if (ch == 'i' ||
		ch == 'I' ||
		ch == 'e' ||
		ch == 'E' ||
		ch == 'a' ||
		ch == 'A' ||
		ch == 'y' ||
		ch == 'Y' ||
		ch == 'u' ||
		ch == 'U' ||
		ch == 'o' ||
		ch == 'O')
		return 1;
	else
		return 0;
}

int main (void) {
	int c, i, j;
	int col_count = 0;
	int len = 0;
	int space_count = 0;
	int vowels = 0;			// we can use smart word wrap if we want (wrap only after vowel char)
	char word[STR_WIDTH];
	char chunk[STR_WIDTH];

	while ((c = getchar()) != EOF) {
		
		/**
		 * if we got space char:
		 *	- insert '\0' at the end of our word[]
		 *	- increase space_count (TAB_WIDTH for '\t' and 1 for ' ')
		 *	- if the word can`t be placed on this line - insert '\n' (and reset col_count)
		 *	- increase col_count by len
		 *	- print the word (it is smaller then line - see last else-block)
		 *	- if spaces can`t be placed on current line - insert '\n' (and reset col_count)
		 *	- putchar
		 *	- increase col_count by space_count
		 *	- reset len
		 */
		if (c == ' ' || c == '\t') {
			word[len] = '\0';
			space_count = (c == '\t') ? TAB_WIDTH : 1;
			if (col_count + len > STR_WIDTH) {
				putchar('\n');
				col_count = 0;
			}
			col_count += len;
			printf("%s", word);
			if (col_count + space_count > STR_WIDTH) {
				putchar('\n');
				col_count = 0;
			}

			putchar(c);
			col_count += space_count;
			len = 0;
		}
		/**
		 * if we got \n:
		 *	- insert '\0' at the end of our word[]
		 *	- if the word can`t be placed on this line - insert '\n'
		 *	- print the word (it is smaller then line - see last else-block)
		 *	- putchar
		 *	- reset len and col_count
		 */
		else if (c == '\n') {
			word[len] = '\0';
			if (col_count + len > STR_WIDTH)
				putchar('\n');
			printf("%s", word);
			putchar(c);
			len = col_count = 0;
		}
		/**
		 * if we got some other char:
		 *	- check if our word` length equals STR_WIDTH - col_count
		 *		- if so, print (STR_WIDTH-1)-word chars, then '-' (the line is now STR_WIDTH long) and '\n'
		 *		- then move word, reset col_count and len
		 *	- insert char into word[], increase len
		 */
		else {
			if (len == 1 && col_count + len ==  STR_WIDTH) {	// otherwise there will be bug in next block
				putchar('\n');
				col_count = 0;
			}
			if (col_count + len >= STR_WIDTH && len > 1) {
				vowels = 0;
				for (j=0, i = 0; i < STR_WIDTH - 1 - col_count; j++, i++) {
					vowels += check_vowel(word[i]);
					chunk[j] = word[i];
					if (check_vowel(word[i]) == 1) {
						chunk[j+1] = '\0';
						printf("%s", chunk);
						for (j = 0; j< i+1; j++)
							chunk[j] = '\0';
						j = 0;
					}
				}
				if (vowels > 0)
					putchar('-');
				putchar('\n');
				chunk[j+1] = '\0';
				printf("%s", chunk);
				word[0] = word[i];	// = word[STR_WIDTH - 1 - col_count];
				len = (STR_WIDTH - col_count) - i;	// = 1;
				col_count = 0;
			}
			word[len] = c;
			len++;
		}
	}
	return 0;
}
