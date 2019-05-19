#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) (x > y ? x : y)

int compare(const void *a, const void *b)
{
	return (int)(*(long long *)a - *(long long *)b);
}

int count_nr_triplets(int n, long long r, long long *arr)
{
	long long nr_triplets;
	long long *nr_prevs;
	int matched, start_pos;
	int i, j;

	nr_prevs = (long long *)calloc(n, sizeof(long long));
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
	long long r;
	long long *arr;
	long long result;
	int i;

	fscanf(stdin, "%d %llu\n", &n, &r);

	arr = (long long *)malloc(n * sizeof(long long));
	for (i = 0; i < n; i++) {
		fscanf(stdin, "%lld", &arr[i]);
	}
	qsort(arr, n, sizeof(long long), compare);

	result = count_nr_triplets(n, r, arr);

	fprintf(stdout, "%lld\n", result);

	free(arr);
	return 0;
}
