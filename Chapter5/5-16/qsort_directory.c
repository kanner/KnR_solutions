/**
 * Exercise 5-16, page 100
 * Упражнение 5.16, страница 132
 *
 * Add the -d ("directory order") option, which makes comparisons only on
 * letters, numbers and blanks. Make sure it works in conjunction with -f.
 *
 * Добавьте в программу ключ -d (от directory order - упорядочение каталожного типа), при
 * наличии которого сравнение должно выполняться только по буквам, цифрам и пробелам.
 * Обеспечьте совместимость этого ключа с -f.
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

char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
	}
	else
		return 0;
}

void afree(char *p)
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

/** Ex. 5-6 */
int _getline_ptr(char *s, int lim)
{
	char c = '\0';
	char *p = s;

	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	*s = '\0';
	return s - p;
}

int readlines(char *lineptr[], int maxlines)
{
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

void writelines(char *lineptr[], int nlines)
{
	printf("\nlines entered:\n");
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

//void swap(char *v[], int i, int j) {
void swap (void *v[], int i, int j)
{
//	char *temp;
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

#include <stdlib.h>

/* numcmp: compare s1 and s2 as numerical */
int numcmp(char *s1, char *s2)
{
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

int numcmp_reverse(char *s1, char *s2)
{
	return (-1)*numcmp(s1, s2);
}

int strcmp_reverse(char *s1, char *s2)
{
	return (-1)*strcmp(s1, s2);
}

/** Ex. 2-10 */
int lower(int c)
{
	return ('A' <= c && c <= 'Z') ? c - 'A' + 'a' : c;
}

/** Ex. 5-15 */
void to_lower(char *source, char *target)
{
	int i;
	for (i = 0; source[i] != '\0'; ++i) {
		target[i] = lower(source[i]);
	}
	target[i] = '\0';
}

int strcmp_incase(char *s1, char *s2)
{
	char _s1[strlen(s1)+1];
	char _s2[strlen(s2)+1];
	to_lower(s1, _s1);
	to_lower(s2, _s2);
	return strcmp(_s1, _s2);
}

int strcmp_reverse_incase(char *s1, char *s2)
{
	return (-1)*strcmp_incase(s1, s2);
}

#include <ctype.h>
/** Ex. 5-5 (strcmp) with editions */
int dircmp(char *s, char *t)
{
//	while(1) {
	while(*s && *t) {
		/** if both symbols are not letter, number or space -- continue */
		if ((!isalnum(*s) && (*s != ' ')) && (!isalnum(*t) && (*t != ' '))) {
			s++;
			t++;
			continue;
		}
		/** if only one is letter, number or space -- return */
		else if (!isalnum(*s) && (*s != ' ')) {
			return -1; // like s < t
		}
		else if (!isalnum(*t) && (*t != ' ')) {
			return 1; // like s > t
		}
		/** if both are letter, number or space -- compare */
		while (((isalnum(*s) && isalnum(*t)) || (*t == ' ' && *s == ' ')) && (*s == *t)) {
//		for ( ; *s == *t; s++, t++) {
			if (*s == '\0')
				return 0;
			s++;
			t++;
		}
		/** if we have no forbidden items left -- break, else -- continue */
		if ((isalnum(*t) || (*t == ' ')) && (isalnum(*s) || (*s == ' ')))
			break;
//			return *s - *t;
	}
	return *s - *t;
}

int dircmp_incase(char *s1, char *s2)
{
	char _s1[strlen(s1)+1];
	char _s2[strlen(s2)+1];
	to_lower(s1, _s1);
	to_lower(s2, _s2);
	return dircmp(_s1, _s2);
}

//void qsort (char *v[], int left, int right) {
void _qsort(void *v[], int left, int right, int (*comp)(void *, void *))
{
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
int main (int argc, char *argv[])
{
	int nlines;
	int numeric = 0;	// 1 -- string of numbers
	int reverse = 0;	// 1 -- reverse order
	int caseinsensitive = 0;// 1 -- case insensitive sort
	int directory = 0;	// 1 -- directory order sort
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
				case 'f':
					caseinsensitive = 1;
					break;
				case 'd':
					directory = 1;
					break;
				}
			}
		}
	}

	/** we can pass caseinsensitive-value if we sort strings as characters (not numeric) */
	if (numeric)
		caseinsensitive = 0;

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
//		qsort(lineptr, 0, nlines - 1);
//		_qsort((void **) lineptr, 0, nlines-1, (int (*)(void*,void*))(numeric ? numcmp : strcmp), reverse);

		if (numeric && reverse)
			comp = (int (*)(void*,void*))numcmp_reverse;
		else if (numeric)
			comp = (int (*)(void*,void*))numcmp;
		else if (caseinsensitive && reverse)
			comp = (int (*)(void*,void*))strcmp_reverse_incase;
		else if (reverse)
			comp = (int (*)(void*,void*))strcmp_reverse;
		else if (caseinsensitive && directory)
			comp = (int (*)(void*,void*))dircmp_incase;
		else if (directory)
			comp = (int (*)(void*,void*))dircmp;
		else if (caseinsensitive)
			comp = (int (*)(void*,void*))strcmp_incase;

		_qsort((void **) lineptr, 0, nlines-1, comp);
		printf("qsort for %s-input in %s order%s%s\n", numeric ? "numeric" : "character", reverse ? "reverse" : "straight", caseinsensitive ? " [case-insensitive]" : "", directory ? " [directory]" : "");
		writelines(lineptr, nlines);
		return 0;
	}
	else {
		printf("error: input too big to sort\n");
		return 1;
	}
}
