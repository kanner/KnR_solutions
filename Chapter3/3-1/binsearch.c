/**
 * Exercise 3-1, page 52
 * Упражнение 3.1, страница 72
 * 
 * Our binary search makes two tests inside the loop, when one would suffice (at
 * the price of more tests outside.) Write a version with only one test inside the loop and measure
 * the difference in run-time.
 *
 * В нашем двоичном поиске каждый цикл содержит две проверки, тогда как достаточно было бы одной
 * (зато взамен их потребовалось бы больше снаружи цикла). Напишите версию функции с одной
 * проверкой внутри цикла и сравните быстродействие (затраты времени).
 */

#include <stdio.h>

int binsearch(int x, int v[], int n) {
	int low, high, mid;

	low = 0;
	high = n - 1;

	while (low <= high) {
		mid = (low + high)/2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;	/* found match */
	}
	return -1;			/* no match */
}

int binsearch_alt(int x, int v[], int n) {
	int low, high, mid;
	
	low = 0;
	high = n-1;
	
	while(low < high) {
		mid = (low + high) / 2;
		if(x <= v[mid])
			high = mid;
		else
			low = mid+1;
	}
	return (x == v[low]) ? low : -1;
}

int main (void) {
	int v[10] = {1,4,7,11,14,21,33,46,102,136};
	printf("%d\n", binsearch(102, v, 10));
	return 0;
}
