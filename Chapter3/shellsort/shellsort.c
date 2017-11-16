
#include <stdio.h>

void shellsort (int v[], int n) {
	int gap, i, j, temp;

	/** расстояние между элементами постепенно уменшается */
	for (gap = n/2; gap > 0; gap /= 2) {
		/** перебор по всем элементам от gap до конца */
		for (i = gap; i < n; i++) {
			/** сравниваем элементы, отделенные gap */
			for (j = i - gap; j >= 0 && v[j] > v[j+gap]; j -= gap) {
				temp = v[j];
				v[j] = v[j+gap];
				v[j+gap] = temp;
			}
		}
	}
}

int main (void) {
	int i = 0;
	int v[11] = {10,8,9,1,2,3,5,4,7,6,0};
	shellsort(v, 11);
	while (i != 11) {
		printf("%d\t", v[i++]);
	}
	printf("\n");
	return 0;
}
