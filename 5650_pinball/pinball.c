#include <stdio.h>
#include <stdlib.h>

#define N_MAX		100
#define map(y, x)	( map[y * width + x] ) 

void map_init(int *width_ptr, int *map)
{
	int x, y;
	int width;

	scanf("%d\n", width_ptr);
	width = *width_ptr;

	for (y = 0; y < width; y++) {
		for (x = 0; x < width; x++) {
			scanf("%d", &map(y, x));
		}
		scanf("\n");
	}
}

int do_pinball(int width, int *map)
{
	int x, y;

	for (y = 0; y < width; y++) {
		for (x = 0; x < width; x++) {
			printf("%d ", map(y, x));
		}
		printf("\n");
	}
}

void print_result(int testnum, int result)
{
	printf("#%d %d\n", testnum, result);
}

void solve_pinball(void)
{
	int T, N;
	int map[N_MAX * N_MAX];

	int t;
	scanf("%d\n", &T);

	for (t = 0; t < T; t++) {
		map_init(&N, map);
		max_point = do_pinball(N, map);
		print_result(t, max_point);
	}
}
int main(void)
{
	solve_pinball();	
	return 0;
}
