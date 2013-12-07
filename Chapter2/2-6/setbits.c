/**
 * Exercise 2-6, page 46
 * Упражнение 2.6, страница 63
 * 
 * Write a function setbits(x,p,n,y) that returns x with the n bits that begin at
 * position p set to the rightmost n bits of y , leaving the other bits unchanged.
 *
 * Напишите функцию setbits(x,p,n,y) так, чтобы она возвращала аргумент x, в котором n
 * битов, начиная с позиции p, равны n крайним правым битам аргумента y, а остальные биты
 * не тронуты.
 */

#include <stdio.h>

//unsigned getbits(unsigned x, int p, int n) {
//	return (x >> (p+1-n)) & ~(~0 << n);
//}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
	int i, j, mask;
	/** rightmost n bits of y */
	i = (x >> (y+1-n)) & ~(~0 << n);
	/** mask with 0`s at the rightmost n bits of p */
	mask = ~(((1 << n) - 1) << (p+1-n));
	/** make zero`s */
	j = mask & x;
	/** replace with rightmost n bits of y */
	return j | i << (p+1-n);
}

int main (void) {
	printf("%0x\n", setbits(120, 4, 3, 7));
	return 0;
}
