/**
 * Exercise 5-12, page 98
 * Упражнение 5.12, страница 129
 * 
 * Extend entab and detab to accept the shorthand
 * entab -m +n
 * to mean tab stops every n columns, starting at column m. Choose convenient (for the user)
 * default behavior.
 *
 * Сделайте так, чтобы программы entab и detab понимали следующую сокращенную запись:
 * entab -m +n
 * Это означает "вставить табуляции каждые n столбцов, начиная со столбца m". Выберите
 * удобные (для пользователя) значения по умолчанию.
 */

#include <stdio.h>
#include <stdlib.h>

#define TAB	8
#define TABULATION(arg1, arg2, arg3)	((arg1 < arg2) ? TAB : arg3)

int entab(int start_pos, int col_per_tab) {
	int i, c;
	/** space counter */
	int space_count = 0;
	int col_count = 0;
	int started_tabbing = 0;

//	while ((c = getchar()) != EOF) {
	while ((c = getchar()) != '\n') {
		/** we should reset column counting if we discovered 'start_pos' */
		if (col_count == start_pos && started_tabbing == 0) {
			col_count = col_count - start_pos;
			started_tabbing = 1;
		}
		/** inserted space char */
		if (c == ' ') {
			space_count++;

			/**
			 * in that way we can use minimum space symbols
			 * we insert TAB when space_count is above next tab stop
			 * note: if we have one space before tab stop - we`ll insert \t instead
			 */
//			if (space_count >= (TAB - (col_count%TAB))) {
			if (space_count >= (TABULATION(col_count, start_pos, col_per_tab) - col_count%TABULATION(col_count, start_pos, col_per_tab))) {
				putchar('\t');
//				space_count = space_count - (TAB - (col_count%TAB));
//				col_count = col_count + (TAB - col_count%TAB);
				space_count = space_count - (TABULATION(col_count, start_pos, col_per_tab) - col_count%TABULATION(col_count, start_pos, col_per_tab));
				col_count = col_count + (TABULATION(col_count, start_pos, col_per_tab) - col_count%TABULATION(col_count, start_pos, col_per_tab));
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

int detab(int start_pos, int col_per_tab) {
	int i, c;
	/** initialized column counter */
	int col_count = 0;
	int started_tabbing = 0;

//	while ((c = getchar()) != EOF) {
	while ((c = getchar()) != '\n') {
		/** we should reset column counting if we discovered 'start_pos' */
		if (col_count == start_pos && started_tabbing == 0) {
			col_count = col_count - start_pos;
			started_tabbing = 1;
		}
		if (c == '\t') {
//			for (i = 0; i < (TAB - col_count%TAB); i++)
			for (i = 0; i < (TABULATION(col_count, start_pos, col_per_tab) - col_count%TABULATION(col_count, start_pos, col_per_tab)); i++)
				putchar(' ');
			/** we inserted space-chars - increase column counter */
//			col_count = col_count + (TAB - col_count%TAB);
			col_count = col_count + (TABULATION(col_count, start_pos, col_per_tab) - col_count%TABULATION(col_count, start_pos, col_per_tab));
		}
		else {
			putchar(c);
			if (c == '\n')
				/** reset column counter */
				col_count = 0;
			else
				/** new character inserted - increase column counter */
				col_count = col_count + 1;
		}
	}
	return 0;
}

int main (int argc, char *argv[]) {
	int start_pos = 0;
	int col_per_tab = TAB;

	if (argc != 3) {
		printf("\nUsage:\n\t%s -m +n\n\tm -\tstart position (column)\n\tn -\tcolumn per TAB\n", argv[0]);
		return 1;
	}
	else {
		if (argv[1][0] == '-')
			start_pos = atoi(argv[1]+1);
		if (argv[2][0] == '+')
			col_per_tab = atoi(argv[2]+1);
	}

	printf("m = %d\nn = %d\n", start_pos, col_per_tab);
	
	printf("\ndoing detab...\n");
	detab(start_pos, col_per_tab);

	printf("\ndoing entab...\n");
	entab(start_pos, col_per_tab);
	printf("\n");
	
	return 0;
}
