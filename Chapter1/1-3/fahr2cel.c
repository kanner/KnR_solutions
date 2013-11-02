/*
 * Exercise 1-3, page 15
 * Упражнение 1.3, страница 27
 * 
 * Modify the temperature conversion program to print a heading above the table.
 *
 * Модифицируйте программу преобразования температур так, чтобы она выводила
 * заголовок над таблицей
 */

#include <stdio.h>

int main (void) {
	float fahr, celsium;
	int lower, upper, step;

	lower = 0;	/* lower limit of temperature table */
	upper = 300;	/* upper limit */
	step = 20;	/* step size */

	fahr = lower;

	printf("fahrenheit\tcelsium\n");
	printf("__________\t_______\n");

	while (fahr <= upper) {
		celsium = (5.0/9.0) * (fahr - 32.0);
		printf("%3.0f\t\t%6.1f\n", fahr, celsium);
		fahr = fahr + step;
	}

	return 0;
}
