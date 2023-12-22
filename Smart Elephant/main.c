#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

struct Elephant {
	int weight;
	int IQ;
	int number;
};

// Function : Comparison
int compare(const void* a, const void* b) {
	struct Elephant* elephant1 = (struct Elephant*)a;
	struct Elephant* elephant2 = (struct Elephant*)b;

	// Sort in ascending order of weight
	if (elephant1->weight < elephant2->weight)
		return -1;
	else if (elephant1->weight > elephant2->weight)
		return 1;
	else {
		// If the same weight, sort in descending order of IQ
		if (elephant1->IQ > elephant2->IQ)
			return -1;
		else if (elephant1->IQ < elephant2->IQ)
			return 1;
		else
			return 0;
	}
}

// Function : Find the longest partial sequence
/*
	Condition Description : 'distance[i] < distance[j] + 1'
		When distance[i] is less than distance[j] + 1, it indicates that a new elephant[i] can be added to the existing partial sequence to form a longer partial sequence.
		--> If you can add elephant[i] to create a longer partial sequence (if distance[i] is less than distance[j] + 1)
		It means adding elephant[i] to the previous partial sequence and updating distance[i] values accordingly
*/
int findMaximum(struct Elephant elephant[], int cnt, int* distance, int* prevIdx) {
	// The prevIdx[i] array represents the index of the element immediately preceding elephant[i] in the longest partial sequence with elephant[i] as the last element	
	for (int i = 0; i < cnt; i++) {
		distance[i] = 0;  // 0 : distance to oneself
		prevIdx[i] = -1;  // -1 : pointing to oneself
		for (int j = 0; j < i; j++) {
			if (elephant[i].weight > elephant[j].weight && elephant[i].IQ < elephant[j].IQ) {
				if (distance[i] < distance[j] + 1) {
					distance[i] = distance[j] + 1;  // Add i as the next element of j -> i is one longer length
					prevIdx[i] = j;
				}
			}
		}
	}
}

// Function : Index Output
void printPath(struct Elephant elephants[], int prevIdx[], int endIndex) {
	// if : If the index does not point to its own index
	if (prevIdx[endIndex] != -1)
		printPath(elephants, prevIdx, prevIdx[endIndex]);
	printf("%d\n", elephants[endIndex].number);
}

int main() {
	FILE* fp = fopen("Input_1.txt", "r");

	if (fp == NULL) {
		printf("Cannot open file\n");
		return -1;
	}

	int lineCnt = 0;
	int temp1 = 0, temp2 = 0;

	// File line centuries
	while (fscanf(fp, "%d %d", &temp1, &temp2) == 2) {
		if (temp1 < 1 || temp1 > 10000) {
			printf("Error : Input Range\n");
			return -1;
		}
		if (temp2 < 1 || temp2 > 10000) {
			printf("Error : Input Rage\n");
			return -1;
		}
		lineCnt++;
	}
	rewind(fp);

	struct Elephant* elephant = (struct Elephant*)malloc(sizeof(struct Elephant) * lineCnt);

	if (elephant == NULL) {
		printf("Memory allocation fail\n");
		return -1;
	}

	int cnt = 0;
	while (lineCnt > 0) {
		fscanf(fp, "%d %d", &elephant[cnt].weight, &elephant[cnt].IQ);
		elephant[cnt].number = cnt + 1;
		lineCnt--; cnt++;
	}
	fclose(fp);

	// Arrange weight in ascending order, and if weight is the same, in descending order based on IQ
	qsort(elephant, cnt, sizeof(struct Elephant), compare);

	int* distance = (int*)malloc(sizeof(int) * cnt);
	int* prevIndex = (int*)malloc(sizeof(int) * cnt);

	if (distance == NULL || prevIndex == NULL) {
		printf("Memory allocation fail\n");
		return -1;
	}

	// Function Call : Find Maximum Length
	findMaximum(elephant, cnt, distance, prevIndex);

	int maxDistance = distance[0], endIndex = 0;

	// Find the index of the longest distance and the elements that have that distance
	for (int i = 1; i < cnt; i++) {
		if (distance[i] > maxDistance) {
			maxDistance = distance[i];
			endIndex = i;
		}
	}

	// Output Result
	printf("%d\n", maxDistance + 1);
	printPath(elephant, prevIndex, endIndex);

	free(elephant);
	free(distance);
	free(prevIndex);

	return 0;
}
