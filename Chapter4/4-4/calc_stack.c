/**
 * Exercise 4-4, page 68
 * Упражнение 4.4, страница 92
 * 
 * Add the commands to print the top elements of the stack without popping, to
 * duplicate it, and to swap the top two elements. Add a command to clear the stack.
 *
 * Добавьте в программу реализацию команд для вывода верхнего элемента стека без
 * его удаления, для создания в стеке дубликата этого элемента и для обмена местами
 * двух верхних элементов. Также реализуйте команду очистки стека.
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

//double stack_show(void) {
//	return val[sp];
//}
void stack_show(void) {
	if (sp > 0)
		printf("stack top: %f\n", val[sp-1]);
	else
		printf("error: stack empty\n");
}

void stack_duplicate(void) {
	double tmp = pop();
	push(tmp);
	push(tmp);
//	push(stack_show());
}

void stack_swap(void) {
	double tmp1 = pop();
	double tmp2 = pop();
	push(tmp1);
	push(tmp2);
}

void stack_clear(void) {
	sp = 0;
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
	int i = 0;
	int c, next_ch;
	
	/** skip space symbpols */
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-')
		/** not number */
		return c;

	/** check if there`s a number or '.' after '-' */
	if (c == '-') {
		next_ch = getch();
		if (!isdigit(next_ch) && next_ch != '.')
			return c;
		c = next_ch;
	}
	else
		c = getch();

	/** collect integer */
	while (isdigit(s[++i] = c))
		c = getch();
	if (c == '.')
		/** collect fraction */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

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
			case '?':
				stack_show();
				break;
			case '#':
				stack_duplicate();
				break;				
			case '~':
				stack_swap();
				break;
			case '!':
				stack_clear();
			case '\n':
				printf("\t%.8f\n", pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}
