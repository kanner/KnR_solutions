/**
 * Exercise 4-3, page 68
 * Упражнение 4.3, страница 92
 * 
 * Given the basic framework, it's straightforward to extend the calculator. Add the
 * modulus (%) operator and provisions for negative numbers.
 *
 * При наличии базовой структуры программы, усовершенствование калькулятора уже
 * не представляет особых трудностей. Реализуйте операцию взятия остатка (%) и
 * работу с отрицательными числами.
 */

#include <stdio.h>
#include <math.h>
#include <ctype.h>

/** max size of operand or operator */
#define MAXOP 100
/** signal that a number was found */
#define NUMBER '0'
/** maximum depth of val stack */
#define MAXVAL 100
/** size of buffer for getch/ungetch */
#define BUFSIZE 100

/** next free stack position */
int sp = 0;
/** value stack */
double val[MAXVAL];
/** buffer for ungetch */
char buf[BUFSIZE];
/** next free position in buf */
int  bufp = 0;

void push (double f) {
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can`t push %f\n", f);
}

double pop (void) {
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

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

int getop (char s[]) {
	int i,c;
	
	/** skip space symbpols */
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-')
		/** not number */
		return c;
	i = 0;
	if (isdigit(c) || c == '-')
		/** collect integer */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')
		/** collect fraction */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

//#define MAXLINE 1000
//int my_getline (char s[], int lim) {
//	/** should be initialized */
//	int c = 0;
//	int i;
//	for (i=0; i < lim-1 && (c = getchar()) != EOF && c !='\n'; i++)
//		s[i] = c;
//	if (c == '\n') {
//		s[i] = c;
//		i++;
//	}
//	s[i] = '\0';
//	return i;
//}

double atof (char s[]) {
	double val, power;
	int i, sign, exp_sign;
	int exp;

	/** skip former space-char`s */
	for (i = 0; isspace(s[i]); i++)
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	/** integer */
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	/** fraction */
	if (s[i] == '.') {
		i++;
		for (power = 1.0; isdigit(s[i]); i++) {
			val = 10.0 * val + (s[i] - '0');
			power *= 10;
		}
		val *= sign / power;
	}

	/** exponent */
	if (s[i] == 'e' || s[i] == 'E') {
		exp_sign = (s[++i] == '-') ? -1 : 1;
		if (s[i] == '+' || s[i] == '-')
			i++;
		for (exp = 0.0; isdigit(s[i]); i++)
			exp = 10.0 * exp + (s[i] - '0');
		val *= pow(10, exp_sign * exp);
	}
//	return sign * val / power;
	return val;
}

/**
 * reverse polish calculator\
 * 1 2 - 4 5 + * == (1 - 2) * (4 + 5)
 */
int main (void) {
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch(type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				/** first pop second operand*/
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: division by zero\n");
				break;
			case '%':
				op2 = pop();
				if (op2 != 0.0)
					push(fmod(pop(), op2));
				else
					printf("error: division by zero\n");
				break;
			case '\n':
				printf("\t%.8f\n", pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;

/*
	double sum = 0;
	char line[MAXLINE];

	while (my_getline(line, MAXLINE) > 0)
		printf("\t%f\n", sum += atof(line));
	return 0;
*/
}
