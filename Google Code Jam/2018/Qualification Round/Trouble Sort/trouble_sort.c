#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

void divide(int *V, int *pair, int *odd, int size);
void join(int *V, int *pair, int *odd, int size);
void quick_sort(int *array, int low, int high);
int verify_wrong_pos(int *V, int size);

int main() {
	int V[MAX], pair[MAX / 2], odd[MAX / 2];
	int T, N;
	int i, wrong_pos, test_case = 0;

	while (scanf("%d", &T) != EOF) {
		while (T > 0) {
			// setup for break
			T -= 1;
			test_case += 1;
			i = 0;

			scanf("%d", &N);

			while (i < N)
				scanf("%d", &V[i++]);

			divide(V, pair, odd, N);
			quick_sort(pair, 0, ((N / 2) + (N % 2)) - 1);
			quick_sort(odd, 0,  (N / 2) - 1);
			join(V, pair, odd, N);

			wrong_pos = verify_wrong_pos(V, N);

			if (wrong_pos == -1)
				printf("Case #%d: OK\n", test_case);
			else
				printf("Case #%d: %d\n", test_case, wrong_pos);
		}
	}

	return 0;
}

void divide(int *V, int *pair, int *odd, int size) {
	int i, j;

	i = 0;
	j = 0;

	while (i < size) {
		pair[j++] = V[i];
		i += 2;
	}

	i = 1;
	j = 0;

	while (i < size) {
		odd[j++] = V[i];
		i += 2;
	}

	return;
}

void join(int *V, int *pair, int *odd, int size) {
	int pair_size = (size / 2) + (size % 2);
	int odd_size = size / 2;
	int i, j;

	i = 0;
	j = 0;

	while (j < pair_size) {
		V[i] = pair[j++];
		i += 2;
	}

	i = 1;
	j = 0;

	while (j < odd_size) {
		V[i] = odd[j++];
		i += 2;
	}

	return;
}

void quick_sort(int *array, int low, int high) {
	int pivot, aux, i, j, mid;

	i = low;
	j = high;

	mid = (i + j) / 2;
	pivot = array[mid];

	do {
		while (array[i] < pivot) i += 1;
		while (array[j] > pivot) j -= 1;

		if (i <= j) {
			aux = array[i];
			array[i] = array[j];
			array[j] = aux;
			i += 1;
			j -= 1;
		}
	} while (j > i);

	if (low < j)
		quick_sort(array, low, j);

	if (i < high)
		quick_sort(array, i, high);

	return;
}

int verify_wrong_pos(int *V, int size) {
	int i = 0;

	while (i < size - 1) {
		if (V[i] > V[i + 1])
			return i;

		i += 1;
	}

	return -1;
}