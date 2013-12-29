/**
 * Exercise 4-8, page 68
 * Упражнение 4.8, страница 93
 * 
 * Suppose that there will never be more than one character of pushback. Modify
 * getch and ungetch accordingly.
 *
 * Предположим, что в поток ввода никогда не будет возвращаться больше одного символа.
 * Доработайте функции getch и ungetch соответственно.
 */

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

/** max size of operand or operator */
#define MAXOP 100
/** signal that a number was found */
#define NUMBER '0'
/** signal that some function was found */
#define FUNCTION_OR_VARIABLE '1'
/** signal that '\0' was found */
#define ENDSTRING '2'
/** maximum depth of val stack */
#define MAXVAL 100
/** size of buffer for getch/ungetch */
#define BUFSIZE 100
/** number of variables */
#define MAXVARS 26
/** variable length */
#define MAX_VAR_NAME 1

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
		printf("pop error: stack empty\n");
		return 0.0;
	}
}

struct var {
	char name[MAX_VAR_NAME+1];
	double value;
};

int var_pos = 0;
struct var last_var;
struct var variables[MAXVARS];

void process_variable(char *name) {
	int i = 0;
	/** trying to find existing variable */
	while(variables[i].name[0] != '\0' && i < MAXVARS - 1) {
		if (strcmp(name, variables[i].name)==0) {
			strcpy(last_var.name, name);
			last_var.value = variables[i].value;
			push(variables[i].value);
			var_pos = i;
			return;
		}
		i++;
	}

	/** if there`s no such variable - add it */
	strcpy(variables[i].name, name);
	strcpy(last_var.name, name);
	last_var.value = variables[i].value;
	push(variables[i].value);
	var_pos = i;
}

void clear_variables(void) {
	int i;
	for (i=0; i < MAXVARS; ++i) {
		variables[i].name[0] = '\0';
		variables[i].value = 0.0;
	}
}

void stack_show(void) {
	if (sp > 0)
		printf("stack top: %f\n", val[sp-1]);
	else
		printf("stack_show error: stack empty\n");
}

void stack_duplicate(void) {
	double tmp = pop();
	push(tmp);
	push(tmp);
}

void stack_swap(void) {
	double tmp1 = pop();
	double tmp2 = pop();
	push(tmp1);
	push(tmp2);
}

void stack_clear(void) {
	sp = 0;
	clear_variables();
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

int buf_alt = EOF;

int getch_one(void) {
	int temp;
	if (buf_alt != EOF) {
		temp = buf_alt;
		buf_alt = EOF;
	}
	else
		temp = getchar();
	return temp;
}

void ungetch_one(int c) {
	if (buf_alt != EOF)
		printf("ungetch: too many characters\n");
	else
		buf_alt = c;
}

/** push entire string back on input */
void ungets(char *s) {    
	size_t i = strlen(s);
	while (i > 0)
		/** we should use back-order, because ungetch uses stack  */
		ungetch(s[--i]);
}

int getop (char s[]) {
	int i = 0;
	int c, next_ch;
	
	/** skip space symbpols */
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';

	if (isalpha(c)) {
		while (isalpha(s[++i] = c = getch()))
			;
		s[i] = '\0';
		if (c != EOF)
			ungetch(c);
		return FUNCTION_OR_VARIABLE;
	}

	if (!isdigit(c) && c != '.' && c != '-') {
		/** assigning a variable */
		if (c == '=' && (next_ch = getch()) == '\n') {
			ungetch('\0');
			return c;
		}
		if (c == '\0')
			return ENDSTRING;
		/** not number */
		return c;
	}

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

void process_function_or_variable(char *name) {
	if (strcmp(name, "sin") == 0)
		push(sin(pop()));
	else if (strcmp(name, "cos") == 0)
		push(cos(pop()));
	else if (strcmp(name, "tan") == 0)
		push(tan(pop()));
	else if (strcmp(name, "exp") == 0)
		push(exp(pop()));
	else if (strcmp(name, "pow") == 0) {
		double op2 = pop();
		double op1 = pop();
		/** division by zero */
		if (op1 == 0 && op2 <= 0)
			printf("error: trying to get \'%f^%f\'\n", op1, op2);
		else
			push(pow(op1, op2));
	}
	/** we`ll use one-letter characters for var`s (string contains only alphabetical characters here) */
	else if (strlen(name) == MAX_VAR_NAME)
		process_variable(name);
	else
		printf("error: unknown command \'%s\'\n", name);
}

/**
 * reverse polish calculator\
 * 1 2 - 4 5 + * == (1 - 2) * (4 + 5)
 */
int main (void) {
	int type;
	double op2;
	char s[MAXOP];
	/** signal that we`ve printed last variable and don`t want to show pop() */
	int last_var_printed = 0;

	clear_variables();

	while ((type = getop(s)) != EOF) {
		switch(type) {
			case NUMBER:
				push(atof(s));
				break;
			case FUNCTION_OR_VARIABLE:
				process_function_or_variable(s);
				break;
			case ENDSTRING:
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
				break;
			case '=':
				/** get '=' from stack - it`s not used */
				pop();
				/** next get real value */
				variables[var_pos].value = pop();
				last_var.value = variables[var_pos].value;
				push(last_var.value);
				break;
			case '$':
				printf("last added value: %s = %f\n", last_var.name, last_var.value);
				last_var_printed = 1;
				break;
			case '\n':
				if (last_var_printed == 0)
					printf("\t%.8f\n", pop());
				else
					last_var_printed = 0;
				break;
			default:
				printf("error: unknown command \'%s\'\n", s);
				break;
		}
	}
	return 0;
}
