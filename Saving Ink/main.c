#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

#define INF DBL_MAX

struct POINT {
    double x;
    double y;
};

// Function : Create adjacency matrix (distance between two points)
double** adjacentMatrix(struct POINT * point, int size) {
    double** matrix = (double**)malloc(sizeof(double*) * size);

    if (matrix == NULL) {
        printf("Error: Memory allocation fail\n");
        exit(-1);
    }

    for (int i = 0; i < size; i++) {
        matrix[i] = (double*)malloc(sizeof(double) * size);
        if (matrix[i] == NULL) {
            printf("Error: Memory allocation fail\n");
            exit(-1);
        }
    }

    // loop : Calculate distances for all paths
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                matrix[i][j] = INF;  // The distance to itself is infinite
            }
            else {
                // Calculating the distance between two points
                double dx = point[i].x - point[j].x;
                double dy = point[i].y - point[j].y;
                matrix[i][j] = sqrt(dx * dx + dy * dy);
            }
        }
    }

    return matrix;
}

// Function : Find index with minimum distance
int minIdx(double weight[], bool set[], int size) {
    double min = INF;
    int minIndex = -1;

    for (int i = 0; i < size; i++) {
        if (!set[i] && weight[i] < min) {
            min = weight[i];
            minIndex = i;
        }
    }

    return minIndex;
}

/// <summary>
/// 91 to 100 line description
/// loop : Repeat until all nodes are visited -> Add one node with minimum distance in each iteration
///     'minIdx' Function : Find the node with the smallest length that has not yet been added to the set
///     loop : Update the minimum length if the condition of the if statement is met
///         if : If it is not included in the set and the length of the path to node v through the selected node is smaller
/// </summary>
/// <param name="matrix">Adjacent matrix</param>
/// <param name="size">Input Count</param>
/// <returns>Sum of minimum length</returns>
double findLength(double **matrix, int size) {
    double* weight = (double*)malloc(sizeof(double) * size);  // Save Minimum Distance
    bool* set = (bool*)malloc(sizeof(bool) * size);  // Whether it is included in the minimum length

    if (weight == NULL || set == NULL) {
        printf("Error: Memory allocation fail\n");
        exit(-1);
    }

    // Initialization
    for (int i = 0; i < size; i++) {
        weight[i] = INF;
        set[i] = false;
    }

    weight[0] = 0;  // Start node: distance 0

    for (int count = 0; count < size - 1; count++) {
        int min = minIdx(weight, set, size);
        set[min] = true;

        for (int v = 0; v < size; v++) {
            if (!set[v] && matrix[min][v] < weight[v]) {
                weight[v] = matrix[min][v];
            }
        }
    }

    // loop: Find the final length
    double result = 0;
    for (int i = 0; i < size; i++) {
        result += weight[i];
    }

    free(weight);
    free(set);
    return result;
}

int main() {
    FILE* fp = fopen("Input_1.txt", "r");

    if (fp == NULL) {
        printf("Error: Cannot open file\n");
        return -1;
    }

    int size = 0;
    fscanf(fp, "%d", &size);

    // Exception handling: input conditions
    if (size <= 0 || size >= 30) {
        printf("Error: Invalid input size\n");
        fclose(fp);
        return -1;
    }

    struct POINT* point = (struct POINT*)malloc(sizeof(struct POINT) * size);

    if (point == NULL) {
        printf("Error: Memory allocation fail\n");
        fclose(fp);
        return -1;
    }

    for (int i = 0; i < size; i++) {
        fscanf(fp, "%lf %lf", &point[i].x, &point[i].y);
    }

    // Function Call : Calculate each distance
    double** matrix = adjacentMatrix(point, size);

    // Output Result
    printf("%.2lf\n", findLength(matrix, size));

    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(point);
    fclose(fp);

    return 0;
}
