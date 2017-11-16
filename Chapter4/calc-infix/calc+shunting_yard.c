/**
###########
known data:
###########
operator	precedence	associativity	operation
^		4		right		exponentiation
*		3		left		multiplication
/		3		left		division
+		2		left		addition
-		2		left		subtraction
(,) 8 - exception?


#####
algo:
#####
while there are tokens to be read:
	read a token.
	if the token is a number, then push it to the output queue.
	if the token is an operator, then:
		while there is an operator at the top of the operator stack with
			greater than or equal precedence and the operator is left associative:
				pop operators from the operator stack, onto the output queue.
		push the read operator onto the operator stack.
	if the token is a left bracket (i.e. "("), then:
		push it onto the operator stack.
	if the token is a right bracket (i.e. ")"), then:
		while the operator at the top of the operator stack is not a left bracket:
			pop operators from the operator stack onto the output queue.
		pop the left bracket from the stack.
		// if the stack runs out without finding a left bracket, then there are
		// mismatched parentheses.
if there are no more tokens to read:
	while there are still operator tokens on the stack:
		// if the operator token on the top of the stack is a bracket, then
		// there are mismatched parentheses.
		pop the operator onto the output queue.
exit.

##########
test data:
##########
3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3

#####
test:
#####

3	Add token to output		3
+	Push token to stack		3			+
4	Add token to output		3 4			+
×	Push token to stack		3 4			× +	× has higher precedence than +
2	Add token to output		3 4 2			× +
÷	Pop stack to output		3 4 2 ×			+	÷ and × have same precedence
Push token to stack			3 4 2 ×			÷ +	÷ has higher precedence than +
(	Push token to stack		3 4 2 ×			( ÷ +
1	Add token to output		3 4 2 × 1		( ÷ +
−	Push token to stack		3 4 2 × 1		− ( ÷ +
5	Add token to output		3 4 2 × 1 5		− ( ÷ +
)	Pop stack to output		3 4 2 × 1 5 −		( ÷ +	Repeated until "(" found
Pop stack				3 4 2 × 1 5 −		÷ +	Discard matching parenthesis
^	Push token to stack		3 4 2 × 1 5 −		^ ÷ +	^ has higher precedence than ÷
2	Add token to output		3 4 2 × 1 5 − 2		^ ÷ +
^	Push token to stack		3 4 2 × 1 5 − 2		^ ^ ÷ +	^ is evaluated right-to-left
3	Add token to output		3 4 2 × 1 5 − 2 3	^ ^ ÷ +
end	Pop entire stack to output	3 4 2 × 1 5 − 2 3 ^ ^ ÷ +

*/


/**
typedef struct {
	// string for number, character with '\0' for operators
	const char *str;
	// precedence (more - higher)
	int prec;
	// associativity (0 - left, 1 - right)
	int assoc;
} str_token_t;
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define INPUT_SIZE  256
/** operator's stack and queue  */
//str_token_t stack[INPUT_SIZE];
//str_token_t queue[INPUT_SIZE];
char stack[INPUT_SIZE];
char queue[INPUT_SIZE];
/** associated pointers */
int sp,qp;
/** associated operations */
#define qpush(x)  queue[qp++]=x
#define spush(x)  stack[sp++]=x
#define spop()   stack[--sp]

void print_queue() {
	int i;
	for (i=0; i<INPUT_SIZE; i++)
		printf("%c", queue[i]);
	printf("\n");
}

void print_stack() {
	int i;
	for (i=0; i<INPUT_SIZE; i++)
		printf("%c", stack[i]);
	printf("\n");
}

int is_operator(char c) {
	switch(c) {
	case '^':
	case '*':
	case '/':
	case '+':
	case '-':
		return 1;
	default:
		return 0;
	}
}

int is_bracket(char c) {
	switch(c) {
	case '(':
		return 1;
	case ')':
		return 2;
	default:
		return 0;
	}
}

int is_number(char c) {
	if (isdigit(c) != 0)
		return 1;
	else
		return 0;
}

int get_operator_precedense(char op) {
	switch (op) {
	case '^':
		return 4;
	case '*':
	case '/':
		return 3;
	case '+':
	case '-':
		return 2;
//    default:
//      printf("Error: no operator %c precedense\n", op);
//      return -1;
	}
	return 0;
}

/** 1 -- left, 2 -- right */
int get_operator_associativity (char op) {
	switch (op) {
	case '^':
		return 2;
	case '*':
	case '/':
	case '+':
	case '-':
		return 1;
//    default:
//      printf("Error: no operator %c associativity\n", op);
//      return -1;
	}
	return 0;
}

int shunting_yard(const char *input, int len) {
	int i;

	// getchar, parse, etc
	for (i = 0; i < len; i++) {
		int isbracket = is_bracket(input[i]);

		if (is_number(input[i])) {
			qpush(input[i]);
//			printf("token %c pushed to queue\n\n", input[i]);
		}
		else if (is_operator(input[i]) || isbracket) {
			/** empy stack -- push */
			if (sp == 0) {
				spush(input[i]);
//				printf("token %c pushed to stack\n\n", input[i]);
			}
			/** check precedense and associativity for operators */
			else if (isbracket == 0) {
				while (get_operator_precedense(input[i]) < get_operator_precedense(stack[sp-1]) ||
				       (get_operator_precedense(input[i]) == get_operator_precedense(stack[sp-1]) &&
					get_operator_associativity(stack[sp-1]) == 1)) {
					qpush(spop());
//					printf("token %c poped from stack\n", queue[qp-1]);
//					printf("token %c pushed to queue\n\n", queue[qp-1]);
				}
				spush(input[i]);
//				printf("token %c pushed to stack\n\n", input[i]);
			}
			/** push opening bracket */
			else if (isbracket == 1) {
				spush(input[i]);
//				printf("token %c pushed to stack\n\n", input[i]);
			}
			/** pop till opening bracket on closing bracket */
			else if (isbracket == 2) {
				while(is_bracket(stack[sp-1])!=1) {
					if (sp == 0) {
						printf("Error: mismatched parentheses detected\n");
						return -1;
					}
					qpush(spop());
//					printf("token %c poped from stack\n", queue[qp-1]);
//					printf("token %c pushed to queue\n\n", queue[qp-1]);
				}
//				printf("token %c is poping from stack\n", stack[sp-1]);
				spop();
			}
		}
		else {
			printf("Error: unknown token %c\n", input[i]);
			return -1;
		}
	}
	/** pop left operators from stack to queue */
	while(sp != 0) {
		char op = spop();
		if (is_bracket(op)==0) {
			qpush(op);
//			printf("token %c pushed to queue\n\n", queue[qp-1]);
		}
		else {
			printf("Error: mismatched parentheses detected\n");
			return -1;
		}
	}
	return 0;
}

/** result stack */
float rstack[INPUT_SIZE]={0};
/** associated pointers */
int rsp;
/** associated operations */
void rspush(float x) {
	rstack[rsp++] = x;
}

float rspop() {
	rstack[rsp] = 0;
	return rstack[--rsp];
}

void print_rstack() {
	int i;
	for (i=0; i<INPUT_SIZE; i++)
		printf("%.2f ", rstack[i]);
	printf("\n\n");
}

int calc_rpn() {
	int i;
	float op2;

	for (i = 0; i < qp; i++) {
		if (is_number(queue[i])) {
//			rspush(atof(queue[i]));
			int num = queue[i] - '0';
			rspush(num);
		}
		else if (is_operator(queue[i])) {
			switch(queue[i]) {
  			case '+':
  				rspush(rspop() + rspop());
				break;
  			case '*':
				rspush(rspop() * rspop());
				break;
  			case '-':
  				/** first pop second operand*/
  				op2 = rspop();
  				rspush(rspop() - op2);
  				break;
  			case '/':
  				op2 = rspop();
  				if (op2 != 0)
  					rspush(rspop() / op2);
  				else {
  					printf("Error: division by zero detected\n");
  					return -1;
  				}
  				break;
  			case '^':
  				op2 = rspop();
  				rspush(powf(rspop(), op2));
  				break;
  			default:
  				printf("Error: unknown operator %c\n", queue[i]);
  				return -1;
			}
		}
		else {
			printf("Error: unknown token %c\n", queue[i]);
			return -1;
		}
	}
	return 0;
}

int main() {
	int res;
//	const char input = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3"
	/** I'll simplify the example -- only numbers and no spaces */
//	const char input[] = "3+4*2/(1-5)^2^3"; // some infix expression
//	const char input[] = "4^2^3";
	const char input[] = "(3+4)*2+2*3";
	int len = strlen(input);

	printf("Processing formula \"%s\"\n\n", input);

	res = shunting_yard(input, len);
	if (res)
		return res;

	printf("Pre-processing complete... Shunting-yard result (reverse Polish notation):\n");
	print_queue();
	printf("\n");

	res = calc_rpn();
	if (res)
		return res;

	printf("Processing complete...\nRPN result = %.9f\n", rspop());
	return 0;
}
