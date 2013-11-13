/**
 * Exercise 1-20, page 34
 * Упражнение 1.20, страница 47
 * 
 * Write a program detab that replaces tabs in the input with the proper number
 * of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns.
 * Should n be a variable or a symbolic parameter?
 *
 * Напишите программу detab, которая бы заменяла символы табуляции во входном потоке соответствующим
 * количеством пробелов до следующей границы табуляции. Предположим, что табуляция имеет фиксированную
 * ширину n столбцов. Следует ли сделать n переменной или символическим параметром?
 */

#include <stdio.h>

#define	TAB	8

int main (void) {
	int i, c;
	int col_count = 0;	// initialized column counter

	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			for (i = 0; i < (TAB - col_count%TAB); i++)
				putchar(' ');
			col_count = col_count + (TAB - col_count%TAB);	// we inserted space-chars - increase column counter
		}
		else {
			putchar(c);
			if (c == '\n')
				col_count = 0;			// reset column counter
			else
				col_count = col_count + 1;	// new character inserted - increase column counter
		}
	}
	return 0;
}

