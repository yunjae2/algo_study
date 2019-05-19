#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) (x > y ? x : y)

int count_nr_triplets(int n, unsigned long long r, unsigned long long *arr)
{
	int nr_triplets;
	int *nr_prevs;
	int matched, start_pos;
	int i, j;

	nr_prevs = (int *)calloc(n, sizeof(int));
	nr_triplets = 0;

	start_pos = 1;
	for (i = 0; i < n; i++) {
		matched = 0;
		for (j = start_pos; j < n; j++) {
			if (arr[j] > r * arr[i])
				break;
			if (arr[j] == r * arr[i]) {
				matched = 1;
				break;
			}
		}
		start_pos = MAX(i + 2, j);

		if (matched) {
			for (; j < n; j++) {
				if (arr[j] > r * arr[i])
					break;
				if (nr_prevs[i]) {
					nr_triplets += nr_prevs[i];
				}
				nr_prevs[j]++;
			}
		}
	}

	return nr_triplets;
}

int main(void)
{
	int n;
	unsigned long long r;
	unsigned long long *arr;
	int result;
	int i;

	fscanf(stdin, "%d %llu\n", &n, &r);

	arr = (unsigned long long *)malloc(n * sizeof(unsigned long long));
	for (i = 0; i < n; i++) {
		fscanf(stdin, "%llu", &arr[i]);
	}

	result = count_nr_triplets(n, r, arr);

	fprintf(stdout, "%d\n", result);

	free(arr);
	return 0;
}
