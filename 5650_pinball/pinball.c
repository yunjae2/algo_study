#include <stdio.h>

#define N_MAX			100
#define pos(y, x)		( (y + 1) * (width + 2) + (x + 1) )
#define map(y, x)		( map[pos(y, x)] )
#define pos_checked(y, x)	( pos_checked[pos(y, x)] )
#define reflect_dir(object, dir_in)	( reflect_dir[object + 1][dir_in] )
#define point_trace(y, x)	( point_trace[pos(y, x)] )
#define tracer(y, x)		( tracer[pos(y, x)] )
#define wormhole_pos(id, num)	( wormhole_pos[id * 2 + num] )

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
	wall_E, wall_S, wall_W,
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

int y_dir[4] = {-1, 0, 1, 0};
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

void map_init(int *width_ptr, enum object *map, int *wormhole_pos)
{
	int x, y;
	int width;
	int worm_id;
	int worm_found[5] = {0, };

	scanf("%d\n", width_ptr);
	width = *width_ptr;

	for (y = -1; y <= width; y++) {
		for (x = -1; x <= width; x++) {
			map(y, x) = 0;
		}
	}

	for (y = 0; y < width; y++) {
		for (x = 0; x < width; x++) {
			scanf("%d", &map(y, x));
		}
		scanf("\n");
	}

	for (worm_id = 0; worm_id < 5; worm_id++) {
		wormhole_pos(worm_id, 0) = 0;
		wormhole_pos(worm_id, 1) = 0;
	}

	for (y = 0; y < width; y++) {
		for (x = 0; x < width; x++) {
			if (map(y, x) >= wormhole_1 &&
					map(y, x) <= wormhole_5) {
				worm_id = map(y, x) - wormhole_1;
				wormhole_pos(worm_id, worm_found[worm_id]++) =
					(y + 1) * (width + 2) + (x + 1);
			}
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

int __follow_path(int start_y, int start_x, int width,
		enum direction start_dir, enum object *map, int *wormhole_pos,
		int *point_trace, int *tracer)
{
	int wormhole_id;
	int warf_pos;

	enum object obj;
	enum object end_obj;

	int ref_dir;
	int point;
	int end_point;
	int max_point = 0;

	int y = start_y;
	int x = start_x;
	int dir = start_dir;
	int current_point = 0;
	int start_pos = (y + 1) * (width + 2) + (x + 1);

	while (1) {
		y += y_dir[dir];
		x += x_dir[dir];
		obj = map(y, x);

		if (obj == way) {
			if (tracer(y, x) == start_pos &&
					max_point <
					current_point - point_trace(y, x)) {
				max_point = current_point - point_trace(y, x);
			}

			point_trace(y, x) = current_point;
			tracer(y, x) = start_pos;
		}
		else if (obj == blackhole) {
			end_point = current_point;
			end_obj = blackhole;
			break;
		}
		else if (obj >= wormhole_1 && obj <= wormhole_5) {
			wormhole_id = obj - wormhole_1;
			if (wormhole_pos(wormhole_id, 0) ==
					(y + 1) * (width + 2) + (x + 1)) {
				warf_pos = wormhole_pos(wormhole_id, 1);
			} else {
				warf_pos = wormhole_pos(wormhole_id, 0);
			}

			y = warf_pos / (width + 2) - 1;
			x = warf_pos % (width + 2) - 1;
		}
		else {
			if (obj != way) {
				ref_dir = reflect_dir(obj, dir);
				if (ref_dir == opposite[dir]) {
					end_point = current_point;
					end_obj = obj;
					break;
				}

				current_point++;
				dir = ref_dir;
			}

			if (tracer(y, x) == start_pos &&
					max_point <
					current_point - point_trace(y, x)) {
				max_point = current_point - point_trace(y, x);
			}

			point_trace(y, x) = current_point;
			tracer(y, x) = start_pos;
		}
	}

	y = start_y;
	x = start_x;
	dir = start_dir;
	current_point = 0;
	while (1) {
		y += y_dir[dir];
		x += x_dir[dir];
		obj = map(y, x);

		if (obj == way) {
			if (point_trace(y, x) == current_point) {
				if (end_obj == blackhole)
					point = end_point - current_point;
				else
					point = (end_point - current_point) *
						2 + 1;

				if (max_point < point) {
					max_point = point;
					break;
				}
			}
		}
		else if (obj == blackhole) {
			break;
		}
		else if (obj >= wormhole_1 && obj <= wormhole_5) {
			wormhole_id = obj - wormhole_1;
			if (wormhole_pos(wormhole_id, 0) ==
					(y + 1) * (width + 2) + (x + 1)) {
				warf_pos = wormhole_pos(wormhole_id, 1);
			} else {
				warf_pos = wormhole_pos(wormhole_id, 0);
			}

			y = warf_pos / (width + 2) - 1;
			x = warf_pos % (width + 2) - 1;
		}
		else {
			ref_dir = reflect_dir(obj, dir);
			if (ref_dir == opposite[dir]) {
				end_point = current_point;
				end_obj = obj;
				break;
			}

			current_point++;
			dir = ref_dir;
		}
	}

	return max_point;
}

int follow_paths(int y, int x, int width, enum object *map, int *wormhole_pos,
	int *point_trace, int *tracer)
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

	max_point = 0;
	for (dq_front = 0; dq_front < dq_rear; dq_front++) {
		start_dir = dirqueue[dq_front];
		path_point = __follow_path(y, x, width, start_dir, map,
				wormhole_pos, point_trace, tracer);
		if (max_point < path_point)
			max_point = path_point;
	}

	return max_point;
}

int do_pinball(int width, enum object *map, int *wormhole_pos)
{
	int x, y;
	int path_point;
	int max_point;

	int pos_checked[(N_MAX + 2) * (N_MAX + 2)] = {0, };
	int point_trace[(N_MAX + 2) * (N_MAX + 2)] = {0, };
	int tracer[(N_MAX + 2) * (N_MAX + 2)] = {0, };

	max_point = 0;
	for (y = -1; y <= width; y++) {
		for (x = -1; x <= width; x++) {
			if (map(y, x) == way)
				continue;

			if (map(y, x) >= wormhole_1 && map(y, x) <= wormhole_5)
				continue;

			path_point = follow_paths(y, x, width, map,
					wormhole_pos, point_trace, tracer);
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
	int wormhole_pos[5 * 2];

	int t;
	scanf("%d\n", &T);

	for (t = 1; t <= T; t++) {
		map_init(&N, map, wormhole_pos);
		max_point = do_pinball(N, map, wormhole_pos);
		print_result(t, max_point);
	}
}

int main(void)
{
	setbuf(stdout, NULL);
	solve_pinball();	
	return 0;
}
