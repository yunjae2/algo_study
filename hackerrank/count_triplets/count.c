#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) (x > y ? x : y)
#define COMB3(n) ((n * (n - 1) * (n - 2)) / 6)
struct array {
	long long val;
	int pos;
};

int compare(const void *a, const void *b)
{
	return (int) ((*(struct array *)a).val - (*(struct array *)b).val);
}

long long count_nr_triplets(int n, long long r, struct array *arr)
{
	long long nr_triplets;
	long long *nr_prevs;
	int matched, start_pos;
	long long group_val;
	long long group_size;
	int i, j;

	nr_prevs = (long long *)calloc(n, sizeof(long long));
	nr_triplets = 0;

	if (r != 1) {
		start_pos = 1;
		for (i = 0; i < n; i++) {
			/* Search for arr[j].val == r * arr[i].val */
			matched = 0;
			for (j = start_pos; j < n; j++) {
				if (arr[j].val > r * arr[i].val)
					break;
				if (arr[j].val == r * arr[i].val) {
					matched = 1;
					break;
				}
			}
			/* Set next start position for searching */
			start_pos = MAX(i + 2, j);

			/*
			 * For all j that arr[i].val == r * arr[j].val,
			 * determine whether arr[j].val is the third value
			 * and save the number of predecessors for
			 * dynamic programming.
			 */
			if (matched) {
				for (; j < n; j++) {
					if (arr[j].val > r * arr[i].val)
						break;
					/*
					 * check if arr[i] is arr[j]'s
					 * predecessor
					 */
					if (arr[i].pos >= arr[j].pos)
						continue;

					if (nr_prevs[i]) {
						nr_triplets += nr_prevs[i];
					}
					nr_prevs[j]++;
				}
			}
		}
	}
	/*
	 * Dedicated path for the case when r equals to 1
	 *
	 * Find the size of each group with same values, and add the number
	 * of 1-triplets to nr_triplets.
	 *
	 */
	else {
		group_val = -1;
		group_size = 0;
		for (i = 0; i < n; i++) {
			if (arr[i].val != group_val) {
				if (group_size >= 3)
					nr_triplets += COMB3(group_size);
				group_val = arr[i].val;
				group_size = 0;
			}
			group_size++;
		}
		if (group_size >= 3) {
			nr_triplets += COMB3(group_size);
		}
	}

	return nr_triplets;
}

int main(void)
{
	int n;
	long long r;
	struct array *arr;
	long long result;
	int i;

	fscanf(stdin, "%d %llu\n", &n, &r);

	arr = (struct array *)malloc(n * sizeof(struct array));
	for (i = 0; i < n; i++) {
		fscanf(stdin, "%lld", &arr[i].val);
		arr[i].pos = i;
	}
	/* sort the array for the algorithm in count_nr_triplets() */
	qsort(arr, n, sizeof(struct array), compare);

	result = count_nr_triplets(n, r, arr);

	fprintf(stdout, "%lld\n", result);

	free(arr);
	return 0;
}
