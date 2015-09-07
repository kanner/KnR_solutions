/**
 * Exercise 1-6, page 19
 * Упражнение 1.6, страница 31
 * 
 * Verify that the expression getchar() != EOF is 0 or 1.
 *
 * Проверьте, что выражение getchar() != EOF действительно равно 1 или 0.
 */

#include <stdio.h>

int main (void) {
	printf("Enter some character.\n");

	// You can try to enter Ctrl+D or Ctrl+Z (EOF)

	printf("'getchar() != EOF' value : %d\n", getchar() != EOF);
	return 0;
}
