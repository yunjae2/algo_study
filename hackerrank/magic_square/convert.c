#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define swap(x, y)	{\
	(x) = (x) + (y);\
	(y) = (x) - (y);\
	(x) = (x) - (y);\
}

char* readline();
char** split_string(char*);

// Complete the formingMagicSquare function below.
int formingMagicSquare(int s_rows, int s_columns, int** s) {
	int cost = 0;

	// edges and vertices should be {2, 4, 6, 8} and {1, 3, 7, 9}
	int magic_vertices[4] = {2, 4, 6, 8};
	int magic_edges[4] = {1, 3, 7, 9};
	int vertices[4] = {s[0][0], s[0][2], s[2][0], s[2][2]};
	int edges[4] = {s[0][1], s[1][0], s[1][2], s[2][1]};

	int i, j;

	// Center element should be 5
	cost += abs(s[1][1] - 5);

	for (i = 0; i < 4; i++) {
		for (j = i + 1; j < 4; j++) {
			if (vertices[i] > vertices[j])
				swap(vertices[i], vertices[j]);
			if (edges[i] > edges[j])
				swap(edges[i], edges[j]);
		}
		cost += abs(vertices[i] - magic_vertices[i]);
		cost += abs(edges[i] - magic_edges[i]);
	}

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

