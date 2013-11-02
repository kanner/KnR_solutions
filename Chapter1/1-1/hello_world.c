/*
 * Exercise 1-1, page 11
 * Упражнение 1.1, страница 21
 * 
 * Run the "hello, world" program on your system. Experiment with
 * leaving out parts of the program, to see what error messages you get.
 *
 * Запустите программу "hello, world" на выполнение в вашей системе.
 * Поэкспериментируйте с ней, выбрасывая определенные фрагменты программы и
 * наблюдая за сообщениями об ошибках, которые будут появляться в связи с этим.
 */

#include <stdio.h>

int main (void) {
	printf("Hello, ");
	printf("world");
	printf("!");
	printf("\n");
	
	printf("Hello, world!\n");

	return 0;
}
