/**
 * Exercise 2-7, page 46
 * Упражнение 2.7, страница 63
 * 
 * Write a function invert(x,p,n) that returns x with the n bits that begin at
 * position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.
 *
 * Напишите функцию invert(x,p,n), возвращающую свой аргумент x, в котором обращены n бит,
 * начиная с позиции p (т.е. единичные биты заменены нулевыми и наоборот), а остальные не
 * тронуты.
 */

#include <stdio.h>

unsigned invert(unsigned x, int p, int n) {
	int mask;
	mask = (~(~0U << n)) << (p-n+1);
	return mask^x;
}

int main (void) {
	printf("%0x\n", invert(240, 4, 3));
	return 0;
}
