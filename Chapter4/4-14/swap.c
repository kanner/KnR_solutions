/**
 * Exercise 4-14, page 76
 * Упражнение 4.14, страница 103
 * 
 * Define a macro swap(t,x,y) that interchanges two arguments of type t.
 * (Block structure will help.)
 *
 * Определите макрос swap(t,x,y), который обменивает местами значения
 * двух аргументов типа t (примените блочную структуру).
 */

#include <stdio.h>

#define swap(t,x,y)	{t tmp; tmp = x; x = y; y = tmp;}

int main (void) {
	int x = 1;
	int y = 2;
	printf("x = %d, y = %d\n", x, y);
	swap(int, x, y);
	printf("x = %d, y = %d\n", x, y);
	return 0;
}
