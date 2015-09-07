/**
 * Exercise 1-5, page 17
 * Упражнение 1.5, страница 28
 * 
 * Modify the temperature conversion program to print the table in reverse order,
 * that is, from 300 degrees to 0
 *
 * Доработайте программу преобразования температур так, чтобы она выводила таблицу
 * в обратном порядке, т.е. от 300 градусов до нуля.
 */

#include <stdio.h>

int main (void) {
	int fahr;
	for (fahr = 300; fahr >= 0; fahr = fahr - 20) {
		printf("%d\t%6.1f\n", fahr, (5.0/9.0) * (fahr - 32.0));
	}
	return 0;
}
