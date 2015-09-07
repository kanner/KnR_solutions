/**
 * Exercise 5-7, page 92
 * Упражнение 5.7, страница 122
 * 
 * Rewrite readlines to store lines in an array supplied by main, rather than
 * calling alloc to maintain storage. How much faster is the program?
 *
 * Перепишите функцию readlines так, чтобы строки помещались в массив,
 * предоставленный функцией main, без вызова alloc для распределения памяти.
 * Насколько быстрее получится программа?
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

#define MAXCACHE 10000

int _readlines(char *lineptr[], int maxlines, char *cache) {
	int len, nlines;
	char *p, line[MAXLEN];

	/** first empty position */
	p = cache + strlen(cache);

	nlines = 0;
	while ((len = _getline_ptr(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (strlen(cache) + len) > MAXCACHE)
			return -1;
		else {
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
			/** next empty position */
			p += len;
		}
	return nlines;
}

void writelines(char *lineptr[], int nlines) {
	printf("\nlines entered:\n");
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

void swap(char *v[], int i, int j) {
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void qsort (char *v[], int left, int right) {
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

int main (void) {
	int nlines;

	char cache[MAXCACHE] = {0};

//	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
	if ((nlines = _readlines(lineptr, MAXLINES, cache)) >= 0) {
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	}
	else {
		printf("error: input too big to sort\n");
		return 1;
	}
}
