/**
 * Exercise 2-1, page 36
 * Упражнение 2.1, страница 50
 * 
 * Write a program to determine the ranges of char, short, int, and long
 * variables, both signed and unsigned, by printing appropriate values from standard headers
 * and by direct computation. Harder if you compute them: determine the ranges of the various
 * floating-point types.
 *
 * Напишите программу для определения диапазонов переменных типов char, short, int и long
 * (как signed, так и unsigned) путем вывода соответствующих значений из заголовочных файлов,
 * а также с помощью непосредственного вычисления. Для второго способа усложним задачу:
 * определите еще и диапазоны вещественных типов.
 */

#include <stdio.h>
#include <limits.h>
/** for pow() only */
#include <math.h>

int main (void) {
	/** variables for calculating */
	unsigned char _char = ~0;
	unsigned short _short = ~0;
	unsigned int _int = ~0;
	unsigned long _long = ~0;

	/** let`s make MAX values for signed (=VAL/2) */
	_char >>= 1;
	_short >>= 1;
	_int >>= 1;
	_long >>= 1;

	printf("limits.h range for 'char': [%d, %d]\n", CHAR_MIN, CHAR_MAX);
	printf("limits.h range for 'signed char': [%d, %d]\n", SCHAR_MIN, SCHAR_MAX);
	/** there`s no UCHAR_MIN in <limits.h> on my system - let`s just calculate (char is 8bit long) */
	printf("limits.h range for 'unsigned char': [%u, %u]\n", (UCHAR_MAX - (int)pow(2,CHAR_BIT) + 1), UCHAR_MAX);
	printf("calculated signed and unsigned char ranges: [%d, %d] and [%d, %u]\n\n", -_char-1, _char, 0, _char*2+1);

	printf("limits.h range for 'short': [%d, %d]\n", SHRT_MIN, SHRT_MAX);
	printf("limits.h range for 'signed short': [%d, %d]\n", SHRT_MIN, SHRT_MAX);
	/** there`s no USHRT_MIN in <limits.h> on my system - there`s a comment that it equals 0 */
	printf("limits.h range for 'unsigned short': [%d, %u]\n", 0, USHRT_MAX);
	printf("calculated signed and unsigned short ranges: [%d, %d] and [%d, %u]\n\n", -_short-1, _short, 0, _short*2+1);

	printf("limits.h range for 'int': [%d, %d]\n", INT_MIN, INT_MAX);
	printf("limits.h range for 'signed int': [%d, %d]\n", INT_MIN, INT_MAX);
	/** there`s no UINT_MIN in <limits.h> on my system - there`s a comment that it equals 0 */
	printf("limits.h range for 'unsigned int': [%d, %u]\n", 0, UINT_MAX);
	printf("calculated signed and unsigned int ranges: [%d, %d] and [%d, %u]\n\n", -_int-1, _int, 0, _int*2+1);

	printf("limits.h range for 'long': [%ld, %ld]\n", LONG_MIN, LONG_MAX);
	printf("limits.h range for 'signed long': [%ld, %ld]\n", LONG_MIN, LONG_MAX);
	/** there`s no ULONG_MIN in <limits.h> on my system - there`s a comment that it equals 0 */
	printf("limits.h range for 'unsigned long': [%d, %lu]\n", 0, ULONG_MAX);
	printf("calculated signed and unsigned long ranges: [%ld, %ld] and [%d, %lu]\n\n", -_long-1, _long, 0, _long*2+1);
	return 0;
}
