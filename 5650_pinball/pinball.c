#include <stdio.h>
#include <stdlib.h>

#define N_MAX			100
#define map(y, x)		( map[(y + 1) * (width + 2) + x + 1] )
#define pos_checked(y, x)	( pos_checked[(y + 1) * (width + 2) + x + 1] )
#define reflect_dir(object, dir_in)	( reflect_dir[object + 1][dir_in] )

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
	wall_W,
	null_object,
	NR_OBJECT_TYPES
};

enum direction {
	N = 0,
	E,
	S,
	W,
	no_dir,
	NR_DIRECTIONS
};

int y_dir[4] = {1, 0, -1, 0};
int x_dir[4] = {0, 1, 0, -1};

enum direction reflect_dir[NR_OBJECT_TYPES][NR_DIRECTIONS] = {
	{no_dir, no_dir, no_dir, no_dir},
	{no_dir, no_dir, no_dir, no_dir},
	{S, W, E, N},
	{E, W, N, S},
	{W, S, N, E},
	{S, N, W, E},
	{S, W, N, E},
	{N, E, S, W},
	{N, E, S, W},
	{N, E, S, W},
	{N, E, S, W},
	{N, E, S, W},
	{no_dir, no_dir, N, no_dir},
	{no_dir, no_dir, no_dir, E},
	{S, no_dir, no_dir, no_dir},
	{no_dir, W, no_dir, no_dir},
};

enum direction opposite[NR_DIRECTIONS] = {S, W, N, E, };

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

int __follow_path(int y, int x, enum direction start_dir, enum object *map,
		int width)
{
	printf("map(%d, %d), startdir: %d\n", y, x, start_dir);

	return 0;
}

int follow_paths(int y, int x, enum object *map, int width)
{
	int path_point;
	int max_point;

	enum object obj;
	enum direction ref_dir;
	enum direction start_dir;

	enum direction dir;

	enum direction dirqueue[NR_DIRECTIONS];
	int dq_front = 0;
	int dq_rear = 0;

	for (dir = N; dir <= W; dir++) {
		obj = map(y, x);
		ref_dir = reflect_dir(obj, dir);
		if (ref_dir == opposite[dir] || obj == blackhole) {
			dirqueue[dq_rear] = opposite[dir];
			dq_rear++;
		}
	}

	for (dq_front = 0; dq_front < dq_rear; dq_front++) {
		start_dir = dirqueue[dq_front];
		path_point = __follow_path(y, x, start_dir, map, width);
		if (max_point < path_point)
			max_point = path_point;
	}

	return max_point;
}

int do_pinball(int width, enum object *map)
{
	int x, y;
	int path_point;
	int max_point;

	int pos_checked[(N_MAX + 2) * (N_MAX + 2)];

	for (y = -1; y <= width; y++) {
		for (x = -1; x <= width; x++) {
			pos_checked(y, x) = 0;
		}
	}

	max_point = 0;
	for (y = -1; y <= width; y++) {
		for (x = -1; x <= width; x++) {
			if (map(y, x) == way)
				continue;

			if (map(y, x) >= wormhole_1 && map(y, x) <= wormhole_5)
				continue;

			path_point = follow_paths(y, x, map, width);
			if (max_point < path_point)
				max_point = path_point;
		}
	}

	return max_point;
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
