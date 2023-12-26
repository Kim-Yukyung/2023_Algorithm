#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/// <summary>
/// First for statement
///		Calculate distance from the point where the health center is located
///		: Find the distance to the nearest health center from my current location
/// Second for statement
///		Calculate distance from point where there is no health center yet
///		1) Find the minimum value between the nearest health center and j, where there is no health center
///		2) Find the largest value among the minimum values
///		3) If the value obtained above is smaller than the current maximum value -> Update the location to place a new health center
///		: Find the optimal location to place a new health center
/// </summary>
/// <param name="matrix">Distance to each vertex</param>
/// <param name="found">Existence of Health Center</param>
/// <param name="size">Input Size</param>
void result(int ** matrix, bool *found, int size) {
	int* minDistance = (int*)malloc(sizeof(int) * size);  // Distance from each point to the nearest health center
	int maxDistance = INT_MIN;  // Save the largest value among the shortest distances

	if (minDistance == NULL) {
		printf("Fail allocated memory\n");
		exit(1);
	}

	// Calculate the distance from each point to the nearest health center
	for (int i = 0; i < size; ++i) {
		minDistance[i] = INT_MAX;

		for (int j = 0; j < size; ++j) {
			// Comparison of the distance to point j, the current health center, with the previous shortest distance
			if (found[j])
				minDistance[i] = (minDistance[i] < matrix[i][j]) ? minDistance[i] : matrix[i][j];
		}
		// Update the largest value of the shortest distance
		maxDistance = (maxDistance > minDistance[i]) ? maxDistance : minDistance[i];
	}

	// Find the optimal location by comparing the distance to the nearest health center for each location
	int result = 0;
	for (int j = 0; j < size; ++j) {
		if (!found[j]) {
			int tempMaxDistance = INT_MIN;

			for (int i = 0; i < size; ++i) {
				int temp = (minDistance[i] < matrix[i][j]) ? minDistance[i] : matrix[i][j];
				tempMaxDistance = (tempMaxDistance > temp) ? tempMaxDistance : temp;
			}

			// Update location and distance if the distance to the current point is less than the previous shortest distance
			if (tempMaxDistance < maxDistance) {
				maxDistance = tempMaxDistance;
				result = j;
			}
		}
	}
	// Result Output
	printf("%d\n", result + 1);
	free(minDistance);
}

// Function: 'Floyd-Warshall' Implementing Algorithms
void floyd(int** adj, bool* found, int size) {
	int** matrix = (int**)malloc(sizeof(int*) * size);
	for (int i = 0; i < size; i++) {
		matrix[i] = (int*)malloc(sizeof(int) * size);
	}

	if (matrix == NULL) {
		printf("Fail allocated memory\n");
		exit(1);
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			matrix[i][j] = adj[i][j];
		}
	}
	for (int k = 0; k < size; k++) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (matrix[i][k] != INT_MAX && matrix[k][j] != INT_MAX) {
					if(matrix[i][j] > matrix[i][k] + matrix[k][j])
						matrix[i][j] = matrix[i][k] + matrix[k][j];
				}
			}
		}
	}

	// Function call: Result Output
	result(matrix, found, size);

	for (int i = 0; i < size; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

int main() {
	FILE* fp = fopen("Input_1.txt", "r");

	if (fp == NULL) {
		printf("Cannot open file\n");
		return -1;
	}

	int healthCenter, vertex;

	fscanf(fp, "%d %d", &healthCenter, &vertex);
	fgetc(fp);

	// Problem Conditions
	if (healthCenter > 100 || vertex > 500) {
		printf("Error: Size of Input\n");
		return -1;
	}

	int** adj = (int**)malloc(sizeof(int*) * vertex);
	for (int i = 0; i < vertex; i++) {
		adj[i] = (int*)malloc(sizeof(int) * vertex);
	}
	int* cnt = (int*)malloc(sizeof(int) * vertex);
	bool* found = (bool*)malloc(sizeof(bool) * vertex);

	if (adj == NULL || cnt == NULL || found == NULL) {
		printf("Fail allocated memory\n");
		return -1;
	}

	// Initialization
	for (int i = 0; i < vertex; i++) {
		found[i] = false;
		cnt[i] = 0;
		for (int j = 0; j < vertex; j++) {
			adj[i][j] = INT_MAX;
			if (i == j)
				adj[i][j] = 0;
		}
	}

	// loop: Save the presence or absence of a health center
	for (int i = 0; i < healthCenter; i++) {
		int cur = 0;
		fscanf(fp, "%d", &cur); fgetc(fp);
		found[cur-1] = true;
	}

	int ver1, ver2, dis;
	bool flag = true;
	// loop: Configure adjacent matrix
	while(fscanf(fp, "%d %d %d", &ver1, &ver2, &dis) == 3) {
		fgetc(fp);
		adj[ver1 - 1][ver2 - 1] = dis; adj[ver2 - 1][ver1 - 1] = dis;
		cnt[ver1 - 1]++; cnt[ver2 - 1]++;
		// Problem condition -> If there are more than 20 connected roads
		if (cnt[ver1 - 1] > 20 || cnt[ver2 - 1] > 20) {
			flag = false;
			break;
		}
	}
	fclose(fp);

	if (flag == false) {
		printf("Error: Number of roads exceeded\n");
		return -1;
	}

	// Function call
	floyd(adj, found, vertex);

	for (int i = 0; i < vertex; i++) {
		free(adj[i]);
	}
	free(adj);
	free(cnt);
	free(found);
	return 0;
}
