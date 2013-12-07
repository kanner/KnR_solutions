/**
 * Exercise 1-21, page 34
 * Упражнение 1.21, страница 47
 * 
 * Write a program entab that replaces strings of blanks by the minimum number
 * of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab . When
 * either a tab or a single blank would suffice to reach a tab stop, which should be given
 * preference?
 *
 * Напишите программу entab, которая бы заменяла пустые строки, состоящие из одних пробелов,
 * строками, содержащими минимальное количество табуляций и дополнительных пробелов, -
 * так, чтобы заполнять то же пространство. Используйте те же параметры табуляции, что и в
 * программе detab. Если для заполнения места до следующей границы табуляции требуется
 * один пробел или один символ табуляции, то что следует предпочесть?
 */

#include <stdio.h>

#define TAB	8

int main (void) {
	int i, c;
	/** space counter */
	int space_count = 0;
	int col_count = 0;

	while ((c = getchar()) != EOF) {
		/** inserted space char */
		if (c == ' ') {
			space_count++;

			/**
			 * in that way we can use minimum space symbols
			 * we insert TAB when space_count is above next tab stop
			 * note: if we have one space before tab stop - we`ll insert \t instead
			 */
			if (space_count >= (TAB - (col_count%TAB))) {
				putchar('\t');
				space_count = space_count - (TAB - (col_count%TAB));
				col_count = col_count + (TAB - col_count%TAB);
			}
//			if (space_count == TAB) {
//				/** if we reached TAB - reset counter and insert tab */
//				putchar('\t');
//				/** we should add space chars that equals the offset from prev tab stop */
//				space_count = col_count%TAB;
//				/** we should add this tab` symbols equivalent to col_count */
//				col_count = col_count + (TAB - col_count%TAB);
//			}
		}
		/** inserted something else */
		else {
			if (space_count > 0) {
				for (i=0; i < space_count; i++) {
					putchar(' ');
					col_count++;
				}
				space_count = 0;
			}
			putchar(c);
			col_count++;
			/** if we start new line - reset column counter */
			if (c == '\n')
				col_count = 0;
		}
	}
	return 0;
}

