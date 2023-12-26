#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct WEIGHT {
    int sum;
    int prev;
};

// Function : Find the minimum value in the previous column
int findMin(int up, int next, int down) {
    int min = up < next ? up : next;
    return down < min ? down : min;
}

// Function : To calculate minimum cost
void findWeight(int row, int column, struct WEIGHT** weight, int** arr) {
    // Initialization : The first weight is its own value
    for (int i = 0; i < row; i++) {
        weight[i][0].sum = arr[i][0];
    }

    for (int j = 1; j < column; j++) {
        for (int i = 0; i < row; i++) {
            // Values above and below the side in the previously
            int up = weight[(i - 1 + row) % row][j - 1].sum;
            int next = weight[i][j - 1].sum;
            int down = weight[(i + 1) % row][j - 1].sum;

            // Function Call : Finding Minimums
            int minValue = findMin(up, next, down);

            // Update weights
            weight[i][j].sum = arr[i][j] + minValue;

            // Save Path
            if (minValue == next)
                weight[i][j].prev = i;
            else if (minValue == up)
                weight[i][j].prev = (i - 1 + row) % row;
            else if (minValue == down)
                weight[i][j].prev = (i + 1) % row;
        }
    }
}


// Function : Compare two paths
int comparePaths(int column, struct WEIGHT** weight, int** arr, int idx1, int idx2) {
    int* temp1 = (int*)malloc(sizeof(int) * column);
    int* temp2 = (int*)malloc(sizeof(int) * column);

    if (temp1 == NULL || temp2 == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    int i, result = 0;

    // loop : Save Path
    for (i = column - 1; i > 0; i--) {
        temp1[i - 1] = weight[idx1][i].prev;
        temp2[i - 1] = weight[idx2][i].prev;
    }
    temp1[column - 1] = idx1;
    temp2[column - 1] = idx2;


    for (int j = 0; j < column && result == 0; j++) {
        if (arr[temp1[j]][j] < arr[temp2[j]][j])
            result = -1;  // idx1 is smaller
        else if (arr[temp1[j]][j] > arr[temp2[j]][j])
            result = 1;  // idx2 is smaller
    }

    free(temp1);
    free(temp2);

    return result;  // if reuslt == 0 : Both paths are the same
}

// Function : Find last row index with minimum cost
int minIndex(int row, int column, struct WEIGHT** weight, int* arr) {
    int min = INT_MAX, rowIdx = 0;
    int minRows[10] = { 0, };  // An array that stores the index of rows with minimum values
    int minRowCnt = 0;  // Number of rows with minimum value

    for (int i = 0; i < row; i++) {
        if (weight[i][column - 1].sum < min) {
            min = weight[i][column - 1].sum;
            minRowCnt = 0;  // Initialize when new minimums are found
            minRows[minRowCnt++] = i;
        }
        else if (weight[i][column - 1].sum == min) {
            minRows[minRowCnt++] = i;  // Add an index if it is equal to the current minimum
        }
    }

    // Lexicographically find the smallest path
    int minIdx = minRows[0];
    for (int i = 1; i < minRowCnt; i++) {
        int currentIdx = minRows[i];
        if (comparePaths(column, weight, arr, currentIdx, minIdx) < 0) {
            minIdx = currentIdx;
        }
    }

    return minIdx;
}

// Function : Results Output
void print(int rowIdx, int column, int** arr, struct WEIGHT** weight) {
    if (column == 1)
        printf("%d ", arr[rowIdx][column - 1]);
    else {
        print(weight[rowIdx][column - 1].prev, column - 1, arr, weight);
        printf("%d ", arr[rowIdx][column - 1]);
    }
}

int main() {
    FILE* fp = fopen("Input_1.txt", "r");

    if (fp == NULL) {
        printf("Cannot open file\n");
        return -1;
    }

    int row = 0, column = 0;

    while (fscanf(fp, "%d %d", &row, &column) == 2) {
        fgetc(fp);

        // Exception handling : input size
        if (row < 1 || row > 10 || column < 1 || column > 100) {
            printf("Error : Input Size\n");
            return -1;
        }

        int** arr = (int**)malloc(sizeof(int*) * row);
        struct WEIGHT** weight = (struct WEIGHT**)malloc(sizeof(struct WEIGHT*) * row);

        for (int i = 0; i < row; i++) {
            arr[i] = (int*)malloc(sizeof(int) * column);
            weight[i] = (struct WEIGHT*)malloc(sizeof(struct WEIGHT) * column);

            for (int j = 0; j < column; j++) {
                fscanf(fp, "%d", &arr[i][j]);
                weight[i][j].sum = 0;
                weight[i][j].prev = 0;
            }
            fgetc(fp);
        }

        // Function Call : Weight Calculation
        findWeight(row, column, weight, arr);

        // Output Results
        int rowIdx = minIndex(row, column, weight, arr);
        print(rowIdx, column, arr, weight);
        printf("\n%d\n", weight[rowIdx][column - 1].sum);

        // Release Memory
        for (int i = 0; i < row; i++) {
            free(arr[i]);
            free(weight[i]);
        }
        free(arr);
        free(weight);
    }
    fclose(fp);
    return 0;
}
