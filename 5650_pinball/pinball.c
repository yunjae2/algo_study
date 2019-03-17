#include <stdio.h>
#include <stdlib.h>

#define N_MAX			100
#define map(y, x)		( map[(y + 1) * (width + 2) + x + 1] )
#define pos_checked(y, x)	( pos_checked[(y + 1) * (width + 2) + x + 1] )

enum object {
	blackhole = -1,
	way,
	block_NE,	// direction of normal vector
	block_SE,
	block_SW,
	block_NW,
	block_square,
	wormhole_1,
	wormhole_2,
	wormhole_3,
	wormhole_4,
	wormhole_5,
	wall_N,
	wall_E,
	wall_S,
	wall_W
};


void map_init(int *width_ptr, enum object *map)
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

	for (x = 0; x < width; x++) {
		map(-1, x) = wall_S;
		map(width, x) = wall_N;
	}

	for (y = 0; y < width; y++) {
		map(y, -1) = wall_E;
		map(y, width) = wall_W;
	}
}

int do_pinball(int width, enum object *map)
{
	int x, y;

	int pos_checked[(N_MAX + 2) * (N_MAX + 2)];

	for (y = -1; y <= width; y++) {
		for (x = -1; x <= width; x++) {
			pos_checked(y, x) = 0;
		}
	}

	return 0;
}

void print_result(int testnum, int result)
{
	printf("#%d %d\n", testnum, result);
}

void solve_pinball(void)
{
	int T, N;
	int max_point;
	enum object map[(N_MAX + 2) * (N_MAX + 2)];

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
