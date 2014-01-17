/**
 * Exercise 5-11, page 98
 * Упражнение 5.11, страница 129
 * 
 * Modify the program entab and detab (written as exercises in Chapter 1) to
 * accept a list of tab stops as arguments. Use the default tab settings if there are no arguments.
 *
 * Усовершенствуйте программы entab и detab (написанные в качестве упражнения в
 * главе 1) так, чтобы они принимали в качестве аргументов командной строки список
 * позиций табуляции. Если аргументы не заданы, должен использоваться заранее
 * заданный стандартный список.
 */

#include <stdio.h>
#include <stdlib.h>

int entab(int tab_default_pos, char **tab_poses) {
	int i, c;
	/** space counter */
	int space_count = 0;
	int col_count = 0;

//	while ((c = getchar()) != EOF) {
	while ((c = getchar()) != '\n') {
		/** inserted space char */
		if (c == ' ') {
			space_count++;

			/**
			 * in that way we can use minimum space symbols
			 * we insert TAB when space_count is above next tab stop
			 * note: if we have one space before tab stop - we`ll insert \t instead
			 */
//			if (space_count >= (TAB - (col_count%TAB))) {
			if (space_count >= (tab_default_pos - (col_count%tab_default_pos))) {
				putchar('\t');
//				space_count = space_count - (TAB - (col_count%TAB));
//				col_count = col_count + (TAB - col_count%TAB);
				space_count = space_count - (tab_default_pos - (col_count%tab_default_pos));
				col_count = col_count + (tab_default_pos - col_count%tab_default_pos);
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

int detab(int tab_default_pos, char **tab_poses) {
	int i, c;
	/** initialized column counter */
	int col_count = 0;

//	while ((c = getchar()) != EOF) {
	while ((c = getchar()) != '\n') {
		if (c == '\t') {
//			for (i = 0; i < (TAB - col_count%TAB); i++)
			for (i = 0; i < (tab_default_pos - col_count%tab_default_pos); i++)
				putchar(' ');
			/** we inserted space-chars - increase column counter */
//			col_count = col_count + (TAB - col_count%TAB);
			col_count = col_count + (tab_default_pos - col_count%tab_default_pos);
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

#define TAB	8

int main (int argc, char *argv[]) {
	int tab_pos = TAB;
	char **tab_poses = NULL;

	if (argc == 2)
		tab_pos = atoi(argv[0]);
	else if (argc > 2)
		tab_poses = argv;

//if (tab_poses != NULL) {
//	printf("tab_poses = %d\n", atoi(tab_poses[1]));
//	printf("tab_poses = %d\n", atoi(tab_poses[2]));
//}

	printf("\ndoing detab...\n");
	detab(tab_pos, tab_poses);

	printf("\ndoing entab...\n");
	entab(tab_pos, tab_poses);
	printf("\n");

	return 0;
}
