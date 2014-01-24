/**
 * Exercise 5-13, page 98
 * Упражнение 5.13, страница 129
 * 
 * Write the program tail, which prints the last n lines of its input. By default, n
 * is set to 10, let us say, but it can be changed by an optional argument so that
 * tail -n
 * prints the last n lines. The program should behave rationally no matter how unreasonable the
 * input or the value of n. Write the program so it makes the best use of available storage; lines
 * should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of
 * fixed size.
 *
 * Напишите программу tail для вывода последних n строк ее входного потока данных.
 * Пусть значение n по умолчанию будет равно, скажем, десяти, но сделайте так, чтобе его
 * можно было изменить необязательным аргументом. Пусть следующая командная строка задает
 * вывод последних n строк:
 * tail -n
 * Программа должна вести себя устойчиво и рационально даже с самыми нелепыми значениями n
 * и содержимым входного потока. Напишите ее так, чтобы она максимально экономно использовала
 * память: строки должны храниться таким образом, как в программе сортировки из раздела 5.6,
 * а не в двумерном массиве фиксированного размера.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <string.h>

#define TAIL 10
#define MAXLEN 1000

/** for alloc(), afree() */
#define ALLOCSIZE 10000
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
	}
	else
		return 0;
}

void afree(char *p) {
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

/** Ex. 5-6 */
int _getline_ptr(char *s, int lim) {
	char c = '\0';
	char *p = s;
	
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	*s = '\0';
	return s - p;
}

void line_shift(char *lineptr[], int shift_size, int nlines) {
	int i;

	strcpy(allocbuf, allocbuf + shift_size);
//	allocp -= shift_size;

	for (i = 1; i < nlines - 1; i++)
		lineptr[i] = lineptr[i+1];
}

int readlines_tail(char *lineptr[], int ntail) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = _getline_ptr(line, MAXLEN)) > 0) {
		if (nlines >= ntail) {
			line_shift(lineptr, strlen(lineptr[0])+1, nlines);
//			nlines--;
			if ((p = alloc(len)) == NULL)
				return -1;
			line[len - 1] = '\0';
			strcpy(p, line);
//			lineptr[nlines++] = p;
			lineptr[nlines - 1] = p;
		}
		else if ((p = alloc(len)) == NULL) {
			return -1;
		}
		else {
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return 0;
}

void writelines(char *lineptr[], int nlines) {
	int i;
	printf("\nlines entered:\n");
	for (i = 0; i < nlines; i++)
		printf("[%d]\t%s\n", i, lineptr[i]);

	printf("\nraw memory:\n");
	for (i = 0; i < ALLOCSIZE; i++)
		printf("%c", allocbuf[i]);
	printf("\n");
}

int main (int argc, char *argv[]) {
	int res;
	int ntail = TAIL;

	if (argc > 2) {
		printf("\nUsage:\n\t%s -n\n\tn -\tnumber of tailed lines\n", argv[0]);
		return 1;
	}
	if (argc == 2 && argv[1][0] == '-') {
		int tmp = atoi(argv[1]+1);
		if (tmp > 0 && tmp < INT_MAX)
			ntail = tmp;
	}

	printf("ntail = %d\n", ntail);

	char *lineptr[ntail];
	res = readlines_tail(lineptr, ntail);
	if (res) {
		printf("error: input too big\n");
		return -1;
	}
	writelines(lineptr, ntail);

	return 0;
}
