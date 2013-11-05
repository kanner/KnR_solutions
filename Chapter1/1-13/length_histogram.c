/*
 * Exercise 1-13, page 25
 * Упражнение 1.13, страница 37
 * 
 * Write a program to print a histogram of the lengths of words in its input. It is
 * easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging.
 *
 * Напишите программу для вывода гистограммы длин слов во входном потоке. Построить гистограмму
 * с горизонтальными рядами довольно легко, а вот с вертикальными столбцами труднее.
 */

#include <stdio.h>

/* подсчет цифр, символов пустого пространства, остальных */
int main (void)
{
	int height = 0;	// the height of vertical histogram
	int c, i, nwhite, nother;
	int ndigit[10];
	
	nwhite = nother = 0;
	for (i = 0; i < 10; i++)
		ndigit[i] = 0;

	while ((c = getchar()) != EOF)
		if (c >= '0' && c <= '9') {
			ndigit[c - '0']++;
			if (ndigit[c - '0'] > height)		// needed for vertical histogram
				height = ndigit[c - '0'];
		}
		else if (c == ' ' || c == '\n' || c == '\t') {
			nwhite++;
			if (nwhite > height)			// needed for vertical histogram
				height = nwhite;
		}
		else {
			nother++;
			if (nother > height)
				height = nother;
		}

	printf("digits =");
	for (i = 0; i < 10; i++)
		printf(" %d", ndigit[i]);
	printf(", white space = %d, other = %d\n",
		nwhite, nother);

	printf("max = %d\n", height);

	printf("\nhorizontal histogram:\n");
	int j;
	for (i = 0; i < 10; i++) {
		printf("digit %d:\t", i+1);
		for (j = 1; j <= ndigit[i]; j++)
			printf("+");
		printf("\n");
	}
	
	printf("white:\t\t");
	for (j = 1; j <= nwhite; j++)
		printf("+");
	printf("\n");

	printf("other:\t\t");
	for (j = 1; j <= nother; j++)
		printf("+");
        printf("\n");

	printf("\nvertical histogram:\n");
	int k;
	for (k = 0; k <= height; k++) {
		for (i = 0; i < 10; i++ ) {			// print digits 0-9 at first
			if (k == 0)
				printf("%d\t", i+1);
			else if (ndigit[i] >= k)
				printf ("+\t");
			else
				printf("\t");
		}
		if (k == 0)					// header extension
			printf("white\tother");
		else {
			if (nwhite >= k)			// then print white spaces
				printf("+\t");
			else
				printf("\t");
			if (nother >= k)			// then print other
				printf("+\t");
			else
				printf("\t");
		}
		printf("\n");
	}

	return 0;
}
