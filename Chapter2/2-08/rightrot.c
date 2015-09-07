/**
 * Exercise 2-8, page 46
 * Упражнение 2.8, страница 63
 * 
 * Write a function rightrot(x,n) that returns the value of the integer x rotated
 * to the right by n positions.
 *
 * Напишите функцию rightrot(x,n), которая бы возвращала значение своего целого
 * аргумента x после его вращения вправо на n двоичных разрядов.
 */

#include <stdio.h>

unsigned rightrot(unsigned x, unsigned n) {
	while (n > 0) {
		if (x & 1)
			x = (x >> 1) | ~(~0U >> 1);
		else
			x = x >> 1;
		n--;
	}
	return x;
}

int main (void) {
	printf("%u\n", rightrot(3, 1));
	return 0;
}
