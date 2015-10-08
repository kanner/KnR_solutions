/**
 * Exercise 5-17, page 100
 * Упражнение 5.17, страница 132
 *
 * Add a field-searching capability, so sorting may bee done on fields within lines,
 * each field sorted according to an independent set of options. (The index for this book was
 * sorted with -df for the index category and -n for the page numbers.)
 *
 * Добавьте в программу возможность обработки полей, т.е. выполнения сортировки по полям внутри
 * строк, причем каждое поле должно сортироваться с независимым набором параметров. (Так,
 * предметный указатель оригинала этой книги был отсортирован с ключом -df по категориям и с
 * ключом -n по номерам страниц.)
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

/** Ex. 5-16 */
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

enum {
	NUMERIC = 0,
	REVERSE,
	CASEINSENSITIVE,
	DIRECTORY,
	OPT_COUNT
};

#define DELIMITER '\t' /** we use tabulation as delimiter */
#define FIELDS_COUNT 10 /** total fields to process */

/** fields` options array */
int options[FIELDS_COUNT][OPT_COUNT] = {{0}};
unsigned int fields_count = 0; // total non-empty fields
int field = 0; // current processing field

//int shift_to_delimiter(char *s1, char *s2) {
	/** pass symbols till DELIMITER */
/*	for (; *s1 != DELIMITER; s1++) {
		if (*s1 == '\n' || *s1 == '\0')
			return 1;
	}
	s1++;

	for (; *s2 != DELIMITER; s2++) {
		if (*s2 == '\n' || *s2 == '\0')
			return 1;
	}
	s2++;

	return 0;
}
*/

int cut_field(char *str) {
	int res = 0;
	/** pass symbols till DELIMITER */
	for (; *str != DELIMITER; str++) {
		if (*str == '\0') {
			res = 1;
			break;
		}
	}
	/** replace delimiter with '\0' */
	*str = '\0';
	return res;
}

int comp_fielded(char *s1, char *s2) {
	int numeric = 0;	// 1 -- string of numbers
	int reverse = 0;	// 1 -- reverse order
	int caseinsensitive = 0;// 1 -- case insensitive sort
	int directory = 0;	// 1 -- directory order sort
	/** compare operation */
	int (*comp)(void*,void*) = (int (*)(void*,void*))strcmp;

	int res = 0;
	int res1 = 0;
	int res2 = 0;
	int field_len1 = 0;
	int field_len2 = 0;
	// set current processing field
	field = 0;

	while (field != fields_count) {
		comp = (int (*)(void*,void*))strcmp;
		numeric = options[field][NUMERIC];
		reverse = options[field][REVERSE];
		caseinsensitive = options[field][CASEINSENSITIVE];
		directory = options[field][DIRECTORY];

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

		/** compare strings only till delimiter */
		res1 = cut_field(s1);
		res2 = cut_field(s2);

		field_len1 = strlen(s1);
		field_len2 = strlen(s2);

		res = comp(s1, s2);
		/** return DELIMITER after cut_field() */
		if (!res1) s1[field_len1] = DELIMITER;
		if (!res2) s2[field_len2] = DELIMITER;
		if (res == 0) {
			/** this error checking is duplicate of while()? */
			if (res1 && res2)
				break;
			else if (res1)
				return -1;
			else if (res2)
				return 1;
			else {
				field++;
//				res = shift_to_delimiter(s1, s2);
				s1 = s1 + field_len1 + 1;
				s2 = s2 + field_len2 + 1;
//				if (res)
//					break;
				continue;
			}
		}
		else
			return res;
	}
	return 0;
}

/** string sorting from stdin */
int main (int argc, char *argv[])
{
	int nlines;
//	int numeric = 0;	// 1 -- string of numbers
//	int reverse = 0;	// 1 -- reverse order
//	int caseinsensitive = 0;// 1 -- case insensitive sort
//	int directory = 0;	// 1 -- directory order sort
	/** compare operation */
//	int (*comp)(void*,void*) = (int (*)(void*,void*))strcmp;
	int z;

	if (argc > 1) {
		int i,j;
		for (i = 1; i < argc; i++) {
//			if (argv[i][0] == '-' && argv[i][2] == '\0') {
//			if (argv[i][0] == '-' && argv[i][1] != '\0') {
			if (argv[i][0] == '-') {
				int empty_field = 1;
			        /** count all possible fields */
			        if (argv[i][1] == '\0') /** assume option '-\0' = base string sort */
					empty_field = 0;
//				fields_count++;
				for(j=1; argv[i][j] != '\0'; j++) {
					switch(argv[i][j]) {
					case 'n':
						options[field][NUMERIC] = 1;
						options[field][CASEINSENSITIVE] = 0;
						empty_field = 0;
						break;
					case 'r':
						options[field][REVERSE] = 1;
						empty_field = 0;
						break;
					case 'f':
						if (options[field][NUMERIC] == 0) {
							options[field][CASEINSENSITIVE] = 1;
							empty_field = 0;
						}
						break;
					case 'd':
						options[field][DIRECTORY] = 1;
						empty_field = 0;
						break;
					}
				}
				if (!empty_field) {
					fields_count++;
					field++;
				}
			}
		}
	}

	/** we can pass caseinsensitive-value if we sort strings as characters (not numeric) */
//	if (numeric)
//		caseinsensitive = 0;

	if (fields_count == 0) {
		printf("error: some options should be specified...\n");
		return 1;
	}
	else {
		if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
/*			int numeric = options[0][NUMERIC];
			int reverse = options[0][REVERSE];
			int caseinsensitive = options[0][CASEINSENSITIVE];
			int directory = options[0][DIRECTORY];
*/
//			qsort(lineptr, 0, nlines - 1);
//			_qsort((void **) lineptr, 0, nlines-1, (int (*)(void*,void*))(numeric ? numcmp : strcmp), reverse);
/*
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
*/
//			_qsort((void **) lineptr, 0, nlines-1, comp);
			_qsort((void **) lineptr, 0, nlines-1, (int (*)(void*,void*))comp_fielded);
//			printf("qsort for %s-input in %s order%s%s\n", numeric ? "numeric" : "character", reverse ? "reverse" : "straight", caseinsensitive ? " [case-insensitive]" : "", directory ? " [directory]" : "");

			printf("qsort for input by fields:\n");
			for (z = 0; z < fields_count; z++) {
				printf("\t [%d]: %s-input in %s order%s%s\n", z, options[z][NUMERIC] ? "numeric" : "character", options[z][REVERSE] ? "reverse" : "straight", options[z][CASEINSENSITIVE] ? " [case-insensitive]" : "", options[z][DIRECTORY] ? " [directory]" : "");
			}

			writelines(lineptr, nlines);
			return 0;
		}
		else {
			printf("error: input too big to sort\n");
			return 1;
		}
	}
//	return 0;
}
