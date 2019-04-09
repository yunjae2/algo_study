#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

// Complete the formingMagicSquare function below.
int formingMagicSquare(int s_rows, int s_columns, int** s) {
	int cost = 0;
	int min_cost_edges = 100;
	int cost_edges;

	int ms[3][3] = {{6, 1, 8}, {7, 5, 3}, {2, 9, 4}};
	int start_mx[4] = {0, 2, 2, 0};
	int start_my[4] = {0, 0, 2, 2};
	int cnt;

	int xdir[4] = {1, 0, -1, 0};
	int ydir[4] = {0, 1, 0, -1};

	int x, y;
	int mx, my;
	int x_lookup, y_lookup;
	int scnt, mcnt;
	int rot;

	// Center element should be 5
	cost += abs(s[1][1] - 5);

	cnt = 0;
	rot = 1;
	do {
		x = 0;
		y = 0;
		cost_edges = 0;
		scnt = 0;
		mx = start_mx[cnt];
		my = start_my[cnt];
		mcnt = cnt;
		do {
			cost_edges += abs(s[y][x] - ms[my][mx]);

			// set next position in s
			x_lookup = x + xdir[scnt];
			y_lookup = y + ydir[scnt];
			if (x_lookup > 2 || x_lookup < 0 ||
					y_lookup > 2 || y_lookup < 0)
				scnt = (scnt + 1) % 4;
			x += xdir[scnt];
			y += ydir[scnt];

			// set next position in ms
			x_lookup = mx + rot * xdir[mcnt];
			y_lookup = my + rot * ydir[mcnt];
			if (x_lookup > 2 || x_lookup < 0 ||
					y_lookup > 2 || y_lookup < 0)
				mcnt = (mcnt + rot * 1 + 4) % 4;
			mx += rot * xdir[mcnt];
			my += rot * ydir[mcnt];
		} while (!(x == 0 && y == 0));

		if (cost_edges < min_cost_edges)
			min_cost_edges = cost_edges;

		// set next starting position / rotation dir in ms
		if (rot == 1)
			rot = -1;
		else {
			cnt++;
			rot = 1;
		}
	} while (cnt < 4);

	cost += min_cost_edges;

	return cost;
}

int main()
{
	FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

	int** s = malloc(3 * sizeof(int*));

	for (int i = 0; i < 3; i++) {
		*(s + i) = malloc(3 * (sizeof(int)));

		char** s_item_temp = split_string(readline());

		for (int j = 0; j < 3; j++) {
			char* s_item_endptr;
			char* s_item_str = *(s_item_temp + j);
			int s_item = strtol(s_item_str, &s_item_endptr, 10);

			if (s_item_endptr == s_item_str || *s_item_endptr != '\0') { exit(EXIT_FAILURE); }

			*(*(s + i) + j) = s_item;
		}
	}

	int s_rows = 3;
	int s_columns = 3;

	int result = formingMagicSquare(s_rows, s_columns, s);

	fprintf(fptr, "%d\n", result);

	fclose(fptr);

	return 0;
}

char* readline() {
	size_t alloc_length = 1024;
	size_t data_length = 0;
	char* data = malloc(alloc_length);

	while (true) {
		char* cursor = data + data_length;
		char* line = fgets(cursor, alloc_length - data_length, stdin);

		if (!line) {
			break;
		}

		data_length += strlen(cursor);

		if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
			break;
		}

		alloc_length <<= 1;

		data = realloc(data, alloc_length);

		if (!line) {
			break;
		}
	}

	if (data[data_length - 1] == '\n') {
		data[data_length - 1] = '\0';

		data = realloc(data, data_length);
	} else {
		data = realloc(data, data_length + 1);

		data[data_length] = '\0';
	}

	return data;
}

char** split_string(char* str) {
	char** splits = NULL;
	char* token = strtok(str, " ");

	int spaces = 0;

	while (token) {
		splits = realloc(splits, sizeof(char*) * ++spaces);

		if (!splits) {
			return splits;
		}

		splits[spaces - 1] = token;

		token = strtok(NULL, " ");
	}

	return splits;
}

