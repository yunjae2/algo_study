#include <stdio.h>
#include <stdlib.h>

int count_nr_triplets(int n, int r, int *arr)
{
	int nr_triplets;
	int *nr_prevs;
	int i, j;

	nr_prevs = (int *)calloc(n, sizeof(int));
	nr_triplets = 0;

	j = 0;
	for (i = 0; i < n; i++) {
		for (; j < n; j++) {
			if (arr[j] > r * arr[i])
				break;
			//printf("comparing %d, %d\n", arr[i], arr[j]);
			if (arr[j] == r * arr[i]) {
				if (nr_prevs[i])
					nr_triplets += nr_prevs[i];
				nr_prevs[j]++;
			}
		}
		j--;
	}

	return nr_triplets;
}

int main(void)
{
	int n, r;
	int *arr;
	int result;
	int i;

	fscanf(stdin, "%d %d\n", &n, &r);

	arr = (int *)malloc(n * sizeof(int));
	for (i = 0; i < n; i++) {
		fscanf(stdin, "%d", &arr[i]);
	}

	result = count_nr_triplets(n, r, arr);

	fprintf(stdout, "%d\n", result);

	free(arr);
	return 0;
}
