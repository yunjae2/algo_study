#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
	return a > b ? a : b;
}

// Complete the nonDivisibleSubset function below.
int nonDivisibleSubset(int k, int S_count, int* S) {
	int i;
	int remainder;

	int *count = (int *)malloc(k * sizeof(int));
	int max_size = 0;

	// Initialize count array
	for (i = 0; i < k; i++)
		count[i] = 0;

	for (i = 0; i < S_count; i++) {
		remainder = S[i] % k;
		count[remainder]++;
	}

	for (i = 1; 2 * i < k; i++) {
		max_size += max(count[i], count[k - i]);
	}

	if (count[0] > 0)
		max_size++;

	if (k % 2 == 0 && count[k / 2] > 0)
		max_size++;

	return max_size;
}

int main()
{
	int result;
	
	int *S;
	int n, k;

	int i;
	
	fscanf(stdin, "%d %d\n", &n, &k);
	S = (int *)malloc(n * sizeof(int));
	
	for (i = 0; i < n; i++)
		fscanf(stdin, "%d", &S[i]);
	
	result = nonDivisibleSubset(k, n, S);

	fprintf(stdout, "%d\n", result);

	return 0;
}
