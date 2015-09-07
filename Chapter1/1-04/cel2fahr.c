/**
 * Exercise 1-4, page 15
 * Упражнение 1.4, страница 27
 * 
 * Write a program to print the corresponding Celsius to Fahrenheit table.
 *
 * Напишите программу для перевода температур по Цельсию в шкалу Фаренгейта
 * и вывода соответствующей таблицы
 */

#include <stdio.h>

int main (void) {
	float fahr, celsium;
	int lower, upper, step;

	/** lower limit of temperature table */
	lower = 0;
	/** upper limit */
	upper = 300;
	/** step size */
	step = 20;

	celsium = lower;

	printf("celsium\tfahrenheit\n");
	printf("_______\t__________\n");

	while (celsium <= upper) {
		fahr = (9.0/5.0) * celsium + 32.0;
		printf("%3.0f\t%6.1f\n", celsium, fahr);
		celsium = celsium + step;
	}

	return 0;
}
