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
#include <limits.h>
#include <string.h>
#include <stdlib.h>

// error codes
#define	STRING_TOO_LONG	1
#define	CACHE_TOO_SMALL	2

#define TAIL 10
#define MAXLEN 1000

/** Ex. 5-6 */
int _getline_ptr(char *s, int lim) {
	char c = '\0';
	char *p = s;

	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	/** error checking */
	else if (c != EOF)
		return -1;
	*s = '\0';
	return s - p;
}

void cleanlines(char *lineptr[], int nlines) {
	int i;
	for (i = 0; i < nlines; i++)
		lineptr[i]='\0';
}

void cleancache(char *cache, int cache_size) {
	int i;
	for (i = 0; i < cache_size; i++)
		cache[i]='\0';
}

void clean_line(char *lineptr, int length) {
	int i;
	for (i = 0; i < length; i++)
		lineptr[i]='\0';
}

void shift_queue(char *lineptr[], char *cache, int ntail) {
	int len = strlen(lineptr[0]) + 1;
	int element = 0;
	char *p = cache;

	/** empty the first element memory */
	clean_line(lineptr[0], len);

	/** shift cache to the left */
	while (element != ntail-1) {
		element++;
		int _len = strlen(lineptr[element]) + 1;

		/** string size could be more then previous one, so we need to copy to buffer */
		char tmp[_len];

		strcpy(tmp,lineptr[element]);
		/** order: we should clean first, then print at previous position (there can be overlap, so we can clean new data) */
		clean_line(lineptr[element], _len);
		strcpy(p, tmp);
//		clean_line(lineptr[element], _len);

		/** update element pointer in lineptr */
//		lineptr[element] = NULL;
		lineptr[element-1] = p;
		p = p + _len;
//		lineptr[element] = p;
	}

	return;

}

int readlines_tailqueue(char *lineptr[], int *ntail, char *cache, int cache_size) {
	int len, nlines;
	char *p, line[MAXLEN];
	int cache_len = strlen(cache);
	int _ntail = *ntail;

	/** first empty position */
	p = cache + strlen(cache);

	nlines = 0;
	while ((len = _getline_ptr(line, MAXLEN)) > 0) {
		/** tail-limit reached -- we should first shift cache and lineptr elements */
		if (nlines >= _ntail) {
			p -= strlen(lineptr[0])+1;
			cache_len -= strlen(lineptr[0])+1;
			shift_queue(lineptr, cache, _ntail);
			nlines--;
		}

		/** populate cache */
		if ((cache_len + len + 1) > cache_size)
			return CACHE_TOO_SMALL;
		else {
			line[len] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
			/** next empty position */
			p += len+1;
			cache_len += len+1;
		}
	}

	/** error checking */
	if (len == -1) {
		*ntail = 0;
		return STRING_TOO_LONG;
	}

	/** update ntail in orfer to pass to writelines() */
	*ntail = nlines;
	return 0;
}

void writelines(char *lineptr[], int nlines, char *cache, int cache_size) {
	int i;
//	printf("\nlines entered:\n");
	for (i = 0; i < nlines; i++)
		// we can write without '\n', cause '\n' is at the end of cached elements
		printf("%s", *lineptr++);
//		printf("%s\n", *lineptr++);
//		printf("[%d]\t%s\n", i, *lineptr++);
/*
	printf("\nraw memory:\n");
	for (i = 0; i < cache_size; i++)
		printf("%c", cache[i]);
	printf("\n");
*/
}

int main (int argc, char *argv[]) {
	int res;
	int ntail = TAIL;

//	char cache[MAXCACHE] = {0};

	if (argc > 2) {
		printf("\nUsage:\n\t%s -n\n\tn -\tnumber of tailed lines\n", argv[0]);
		return 1;
	}
	if (argc == 2 && *(argv+1)[0] == '-') {
		int tmp = atoi(argv[1]+1);
		if (tmp > 0 && tmp < INT_MAX)
			ntail = tmp;
	}

//	printf("info: ntail = %d\n", ntail);

	char cache[MAXLEN*ntail];
	char *lineptr[ntail];
	cleanlines(lineptr, ntail);
	cleancache(cache, MAXLEN*ntail);

	res = readlines_tailqueue(lineptr, &ntail, cache, MAXLEN*ntail);
	if (!res) {
		writelines(lineptr, ntail, cache, MAXLEN*ntail);
		return 0;
	}
	else {
		switch(res) {
			case STRING_TOO_LONG:
				printf("error: too long string in input\n");
				break;
			case CACHE_TOO_SMALL:
				printf("error: cache too small to store %d strings, this shouldn`t happen...\n", ntail);
				break;
			default:
				printf("error: unknown error code occured\n");
				break;
		}
		return res;
	}
}
