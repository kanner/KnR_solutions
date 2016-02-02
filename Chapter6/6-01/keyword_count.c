/**
 * Exercise 6-01, page 112
 * Упражнение 6.01, страница 147
 *
 * Our version of getword does not properly handle underscores, string
 * constants, comments, or preprocessor control lines. Write a better version.
 *
 * Наша версия getword не умеет корректно обрабатывать знаки подчеркивания,
 * строковые константы, комментарии и управляющие строки
 * препроцессора. Усовершенствуйте эту функцию соответствующим образом.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof keytab[0])

struct key {
	char *word;
	int count;
} keytab [] = {
	/** here we added preprocessor control lines, use correct order! */
	{"#define", 0},
	{"#undef", 0},
	{"#include", 0},
	{"#line", 0},
	{"#error", 0},
	{"#pragma", 0},
	{"#if", 0},
	{"#ifdef", 0},
	{"#ifndef", 0},
	{"#elif", 0},
	{"#else", 0},
	/** original words */
	{"auto", 0},
	{"break", 0},
	{"case", 0},
	{"char", 0},
	{"const", 0},
	{"continue", 0},
	{"default", 0},
	/* ... */
	{"printf", 0},
	{"return", 0},
	/** only for testing purposes, word should not start with '_' */
	{"test_word", 0},
	{"unsigned", 0},
	{"void", 0},
	{"volatile", 0},
	{"while", 0},
};

/** Ex. 4-4 */
/** size of buffer for getch/ungetch */
#define BUFSIZE 100
/** buffer for ungetch */
char buf[BUFSIZE];
/** next free position in buf */
int  bufp = 0;

/** get a (possibly pushed back) character */
int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/** push character back on input */
void ungetch(int c) {
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/** like Ex. 3-01 */
int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low+high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	/** no match */
	return -1;
}

/** we don`t process several stars like in "/" + "**" */
int ext_syms(char sym, int beginning) {
	int res = 0;
	char next;

	switch(sym) {
	  /** word should not start with '_'? */
	  case '_':
		  if (beginning == 1)
			  res = -1;
		  else
			  res = 0;
		  break;
	  case '"':
		  /** restart or end word processing. we would not process
		      special values like '\n', etc -- only full values
		      included in keytab[] */
		  res = -1;
		  break;
	  case '#':
		res = 0;
		break;
	  /** comments need one more character to check */
          case '/':
		  if ((next = getch()) == '/' || next == '*')
			  res = next;
		  else {
			  ungetch(next);
			  res = -1;
		  }
		  break;
          case '*':
		  if ((next = getch()) == '/')
			  res = next;
		  else if (next == '*')
			  res = next;
		  else {
			  ungetch(next);
			  res = -1;
		  }
		  break;
	  default:
		  res = -1;
		  break;
	}
	return res;
}

int getword_ext(char *w, int *lim, int beginning) {
	int res = 0;
	int c;

	if ((c = ext_syms(*w, beginning)) == -1) {
		ungetch(*w);
		res = -1;
	}
	/** populate next character for comments */
	else if (c > 0) {
//		w++;
//		lim--;
//		*w = c;
		res = c;
	}
	return res;
}

int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w = c;
	/** this should be used because EOF doesn`t return to stdin (in
	    getword_ext()) and we get previous character on next getch()!
	    Why...? */
	else
		return c;
	/** added check for extended character values */
	if (!isalpha(c)) {
		if ((c = getword_ext(w, &lim, 1)) < 0) {
			c = getch();
			w++;
			*w = '\0';
			return c;
		}
		else if (c > 0) {
			w++;
			lim--;
			*w = c;
		}
	}
	w++;
	for ( ; --lim > 0; w++) {
		/** added check for extended character values */
		if (!isalnum(*w = getch()) /*&& w != '_'*/) {
			if ((c = getword_ext(w, &lim, 0)) < 0)
				break;
			else if (c > 0) {
				w++;
				lim--;
				*w = c;
			}
		}
	}
	*w = '\0';
	return word[0];
}

int main (void) {
	int n;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) || ext_syms(word[0], 1) == 0)
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;
	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n",
			       keytab[n].count, keytab[n].word);
	return 0;
}
