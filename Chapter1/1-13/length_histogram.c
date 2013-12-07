/**
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

#define	IN		1
#define OUT		0
#define MAXWORDLEN	10

int main (void)
{
	int c, i;
	int word_length = 0;
	/** the height of vertical histogram */
	int height = 0;
	int state = OUT;
	/** array of word length`s, [MAXWORDLEN] - length above MAXWORDLEN */
	int length[MAXWORDLEN+1]={0};
	c = i = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			state = OUT;
			if (word_length <= 10)
				length[word_length-1]++;
			else
				length[MAXWORDLEN]++;
			word_length = 0;
		}
		else if (state == OUT) {
			state = IN;
			word_length++;
		}
		else if (state == IN) {
			word_length++;
		}
	}

	printf("length =");
	for (i = 0; i <= 10; i++) {
		/** needed for vertical histogram */
		if (length[i]>height)
			height = length[i];
		printf(" %d", length[i]);
	}
	printf("\nmax = %d\n", height);

	printf("\nhorizontal histogram:\n");
	int j;
	for (i = 0; i <= 10; i++) {
		if (i < 10)
			printf("len=%d\t[%d]:\t", i+1, length[i]);
		else
			printf("len>10\t[%d]:\t", length[i]);
		for (j = 1; j <= length[i]; j++)
			printf("+");
		printf("\n");
	}
	
	printf("\nvertical histogram:\n");
	for (i = 0; i <= height; i++) {
		for (j = 0; j <= 10; j++ ) {
			/** header */
			if (i == 0) {
				if (j == 10)
					printf(">10 [%d]\t", length[j]);
				else
					printf("%d [%d]\t", j+1, length[j]);
			}
			else if (length[j] >= i)
				printf ("+\t");
			else
				printf("\t");
		}
		printf("\n");
	}

	return 0;
}
