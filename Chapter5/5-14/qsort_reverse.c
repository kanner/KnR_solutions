/**
 * Exercise 5-14, page 100
 * Упражнение 5.14, страница 132
 *
 * Modify the sort program to handle a -r flag, which indicates sorting in reverse
 * (decreasing) order. Be sure that -r works with -n.
 *
 * Доработайте программу сортировки так, чтобы она обрабатывала ключ -r, требующий
 * сортировки в обратном порядке (по убыванию). Сделайте так, чтобы ключ -r работал
 * и при наличии ключа -n.
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];
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

int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = _getline_ptr(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

void writelines(char *lineptr[], int nlines) {
	printf("\nlines entered:\n");
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

//void swap(char *v[], int i, int j) {
void swap (void *v[], int i, int j) {
//	char *temp;
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

#include <stdlib.h>

/* numcmp: compare s1 and s2 as numerical */
int numcmp(char *s1, char *s2) {
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);

	// error checking here?

	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int numcmp_reverse(char *s1, char *s2) {
	return (-1)*numcmp(s1, s2);
}

int strcmp_reverse(char *s1, char *s2) {
	return (-1)*strcmp(s1, s2);
}

//void qsort (char *v[], int left, int right) {
void _qsort(void *v[], int left, int right, int (*comp)(void *, void *)) {
	int i, last;
	void swap(void *v[], int i, int j);
//	void swap(char *v[], int i, int j);

	if (left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
//		if (strcmp(v[i], v[left]) < 0)
//		if ((reverse ? ((*comp)(v[i], v[left]) > 0) : ((*comp)(v[i], v[left]) < 0)))
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
//	qsort(v, left, last - 1);
	_qsort(v, left, last - 1, comp);
//	qsort(v, last + 1, right);
	_qsort(v, last + 1, right, comp);
}

/** string sorting from stdin */
int main (int argc, char *argv[]) {
	int nlines;
	int numeric = 0;	// 1 -- string of numbers
	int reverse = 0;	// 1 -- reverse order
	/** compare operation */
	int (*comp)(void*,void*) = (int (*)(void*,void*))strcmp;

	if (argc > 1) {
		int i;
		for (i = 1; i < argc; i++) {
			if (argv[i][0] == '-' && argv[i][2] == '\0') {
				switch(argv[i][1]) {
				case 'n':
					numeric = 1;
					break;
				case 'r':
					reverse = 1;
					break;
				}
			}
		}
	}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
//		qsort(lineptr, 0, nlines - 1);
//		_qsort((void **) lineptr, 0, nlines-1, (int (*)(void*,void*))(numeric ? numcmp : strcmp), reverse);

		if (numeric && reverse)
			comp = (int (*)(void*,void*))numcmp_reverse;
		else if (numeric)
			comp = (int (*)(void*,void*))numcmp;
		else if (reverse)
			comp = (int (*)(void*,void*))strcmp_reverse;

		_qsort((void **) lineptr, 0, nlines-1, comp);
		printf("qsort for %s-input in %s order\n", numeric ? "numeric" : "character", reverse ? "reverse" : "straight");
		writelines(lineptr, nlines);
		return 0;
	}
	else {
		printf("error: input too big to sort\n");
		return 1;
	}
}
