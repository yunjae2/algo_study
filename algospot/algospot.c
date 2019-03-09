#include <stdio.h>

#define N_MAX		100
#define M_MAX		100
#define map(y, x)	( map[y * width + x] )
#define nr_break(y, x)	( nr_break[y * width + x] )

int dir_x[4] = {1, 0, -1, 0};
int dir_y[4] = {0, 1, 0, -1};

struct position {
	int x;
	int y;
};

struct queue {
	int front;
	int rear;
	struct position pos[N_MAX * M_MAX];
};

void map_init(int *N_ptr, int *M_ptr, int *map)
{
	int i, j;
	int width, height;
	char c;

	scanf("%d %d\n", M_ptr, N_ptr);
	width = *M_ptr;
	height = *N_ptr;

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			c = getchar();
			map(i, j) = c - '0';
		}
		c = getchar();
	}
}

int find_path(int height, int width, int *map)
{
	int x, y;
	int sx, sy;
	int nr_break[N_MAX * M_MAX];
	
	struct queue room_queue, wall_queue;
	room_queue.front = 0;
	room_queue.rear = 0;
	wall_queue.front = 0;
	wall_queue.rear = 0;

	int angle;

	for (y = 0; y < height; y++) 
		for (x = 0; x < width; x++)
			nr_break(y, x) = height * width;

	nr_break(0, 0) = 0;

	x = 0;
	y = 0;
	while(x != width - 1 || y != height - 1) {
		for (angle = 0; angle < 4; angle++) {
			sx = x + dir_x[angle];
			sy = y + dir_y[angle];

			if (sx < 0 || sx >= width)
				continue;
			if (sy < 0 || sy >= height)
				continue;
			
			if (map(sy, sx) == 0 &&
					nr_break(sy, sx) > nr_break(y, x)) {
				if (sx == width - 1 && sy == height - 1)
					return nr_break(y, x);

				nr_break(sy, sx) = nr_break(y, x);
				room_queue.pos[room_queue.rear].x = sx;
				room_queue.pos[room_queue.rear].y = sy;
				room_queue.rear++;
			} else if (map(sy, sx) == 1 &&
					nr_break(sy, sx) > nr_break(y, x) + 1) {
				nr_break(sy, sx) = nr_break(y, x) + 1;
				wall_queue.pos[wall_queue.rear].x = sx;
				wall_queue.pos[wall_queue.rear].y = sy;
				wall_queue.rear++;
			}
		}
		
		if (room_queue.front < room_queue.rear) {
			x = room_queue.pos[room_queue.front].x;
			y = room_queue.pos[room_queue.front].y;
			room_queue.front++;
		} else if (wall_queue.front < wall_queue.rear) {
			x = wall_queue.pos[wall_queue.front].x;
			y = wall_queue.pos[wall_queue.front].y;
			wall_queue.front++;
		} else {
			printf("something is wrong\n");
			break;
		}
	}

	return nr_break(y, x);
}

int main(void)
{
	int N, M;
	int map[N_MAX * M_MAX];
	int res;

	map_init(&N, &M, map);

	res = find_path(N, M, map);
	
	printf("%d\n", res);

	return 0;
}
