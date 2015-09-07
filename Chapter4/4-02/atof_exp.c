/**
 * Exercise 4-2, page 63
 * Упражнение 4.2, страница 87
 * 
 * Extend atof to handle scientific notation of the form 123.45e-6
 * where a floating-point number may be followed by e or E and an optionally signed exponent.
 *
 * Усовершенствуйте функцию atof так, чтобы она понимала экспоненциальную запись
 * чисел вида 123.45e-6. В этой записи после вещественного числа может следовать
 * символ e или E, а затем показатель степени - возможно, со знаком.
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>

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

int main (void) {
	printf("%f\n", atof("123.45e-2"));
	printf("%f\n", atof("0.1e-2"));
	return 0;
}
