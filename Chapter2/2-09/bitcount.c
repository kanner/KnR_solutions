/**
 * Exercise 2-9, page 47
 * Упражнение 2.9, страница 65
 * 
 * In a two's complement number system, x&=(x-1) deletes the rightmost 1-bit
 * in x. Explain why. Use this observation to write a faster version of bitcount.
 *
 * Благодаря свойствам двоичной системы счисления выражение x&=(x-1) удаляет
 * самый правый единичный бит в переменной x. Докажите это. Воспользуйтесь
 * этим фактом для того, чтобы написать более быструю версию функции bitcount.
 */

#include <stdio.h>

unsigned bitcount(unsigned x) {
	int b;
	for (b = 0; x != 0; x &= (x-1))
		b++;
	return b;
}

int main (void) {
	printf("%d\n", bitcount(0777));
	return 0;
}
