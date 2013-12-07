/**
 * Exercise 1-15, page 28
 * Упражнение 1.15, страница 40
 * 
 * Rewrite the temperature conversion program of Section 1.2 to use a function
 * for conversion.
 *
 * Перепишите программу преобразования температур из раздела 1.2 так, чтобы
 * само преобразование выполнялось функцией
 */

#include <stdio.h>

float fahr2cel (float fahr) {
	return ((5.0/9.0) * (fahr - 32.0));
}

int main (void) {
	float fahr, celsium;
	int lower, upper, step;

	/** lower limit of temperature table */
	lower = 0;
	/** upper limit */
	upper = 300;
	/** step size */
	step = 20;

	fahr = lower;

	printf("fahrenheit\tcelsium\n");
	printf("__________\t_______\n");

	while (fahr <= upper) {
//		celsium = (5.0/9.0) * (fahr - 32.0);
		celsium = fahr2cel (fahr);
		printf("%3.0f\t\t%6.1f\n", fahr, celsium);
		fahr = fahr + step;
	}

	return 0;
}
