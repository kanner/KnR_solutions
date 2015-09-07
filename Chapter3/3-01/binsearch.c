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
#include <time.h>

#define MASSIVE_SIZE 1000000

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
			/** found match */
			return mid;
	}
	/** no match */
	return -1;
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
	clock_t timer;
	int pos = 0;
	int i;
//	int v[10] = {1,4,7,11,14,21,33,46,102,136};
	int v[MASSIVE_SIZE] = {0};

	for (i = 0; i < MASSIVE_SIZE; ++i)
		v[i] = i;

	timer = clock();
	for (i = 0; i < MASSIVE_SIZE; ++i) {
//		pos = binsearch(i, v, MASSIVE_SIZE);
//		/** let`s use the worst value to search */
		pos = binsearch(-1, v, MASSIVE_SIZE);
//		printf("%d\n", pos);
	}
	timer = clock() - timer;

	printf("originl results:\n\ttimer: %lu clocks or %lu seconds\n", timer, timer/CLOCKS_PER_SEC);

	timer = clock();
	for (i = 0; i < MASSIVE_SIZE; ++i) {
//		pos = binsearch_alt(i, v, MASSIVE_SIZE);
//		/** let`s use the worst value to search */
		pos = binsearch_alt(-1, v, MASSIVE_SIZE);
//		printf("%d\n", pos);
	}
	timer = clock() - timer;

	printf("alternative results:\n\ttimer: %lu clocks or %lu seconds\n", timer, timer/CLOCKS_PER_SEC);
	return 0;
}
