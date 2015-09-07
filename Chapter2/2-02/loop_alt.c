/**
 * Exercise 2-2, page 40
 * Упражнение 2.2, страница 56
 * 
 * Write a loop equivalent to the for loop above without using && or ||.
 *
 * Напишите цикл, эквивалентный приведенному выше циклу for, не используя операции && и ||.
 */

#include <stdio.h>

#define LENGTH	20

int main (void) {
	int i = 0;
	int lim, c;
	lim = LENGTH;
	char s[LENGTH] = {0};

	/** real loop */
//	for (i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
//		s[i] = c;

	/** loop equivalent */
	while (i<lim-1) {
		if ((c = getchar()) == '\n')
			break;
		else if (c == EOF)
			break;
		else
			s[i++] = c;
	}

	s[i] = '\0';
	printf("%s\n", s);
	
	return 0;
}
