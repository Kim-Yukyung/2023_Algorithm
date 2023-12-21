#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 30

// Function : Implement the 'filp' function (to reverse the order of the arrangement)
void filp(int arr[], int index) {
    int temp = 0;

    // Interchange both ends
    for (int i = 0; i < (index + 1) / 2; i++) {
        temp = arr[i];
        arr[i] = arr[index - i];
        arr[index - i] = temp;
    }
}

// Function : Found index of maximum value in current array
int findMaxIndex(int arr[], int end) {
    int index = 0;
    for (int i = 1; i < end; i++) {
        if (arr[index] < arr[i])
            index = i;

        // If the maximum value is the same as the current value
        else if(arr[index] == arr[i]){
            // If the current index is the last one, return the last one
            // Reason : Last index must be returned to move on without 'filp'
            if (i == end - 1)
                index = end - 1;
            // Return the first index if the maximum index is the first index
            // Reason: 'Filp' can only be performed once if the first index is returned
            else if (index == 0)
                index = 0;
            // If the maximum value is continuous, return the index after it
            // Reason : The number of 'flip' can be minimized by performing 'flip', 
            // while continuous maximums remain in state only when the index behind them is returned
            // Ex : 1 2 2 1 (return 2) -> filp : 2 2 1 1 -> filp : 1 1 2 2
            // === If return 1 -> filp : 2 1 2 1 -> filp : 1 2 1 2 ... ===
            else if (i == index + 1)
                index = i;
        }
    }
    return index;
}

// Function : Implement the ability to output arrays
void printFun(int arr[], int index) {
    for (int i = 0; i < index; i++) {
        printf("%d", arr[i]);
        // Add a space if it is not the last element
        if (i != index - 1)
            printf(" ");
    }
}

int main() {
    FILE* fp = fopen("Input_1.txt", "r");

    // Exception handling
    if (fp == NULL) {
        printf("Error : Cannot open the file\n");
        return -1;
    }

    char line[100];
    while (fgets(line, sizeof(line), fp) != NULL) {
        // Remove newline characters at the end of a string
        if(line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        printf("%s", line);

        int num[SIZE];  // [0] : Top, [SIZE - 1] : Bottom
        int count = 0;
        bool flag = true;
        char* token = strtok(line, " ");

        // loop : Store entered values in an array
        while (token != NULL) {
            int temp = atoi(token);

            // Exception handling : Number of inputs exceeded
            if (count >= 30) {
                printf(" Error : Number of inputs exceeded\n");
                flag = false;
                break;
            }

            // Exception handling : Out of diameter range (1-10)
            if (temp < 1 || temp > 10) {
                printf(" Error : Input range\n");
                flag = false;
                break;
            };

            num[count++] = temp;  
            token = strtok(NULL, " ");
        }

        // Exit if conditions are not met
        if (flag == false)
            continue;

        int resultCnt = 0;
        int results[100];

        // loop : Hold the largest value in the array last and sort by decreasing the size of the array one by one
        for (int i = 0; i < count - 1; i++) {
            int maxIndex = findMaxIndex(num, count - i);

            // If the largest value is at the end (below) of the current range
            if (maxIndex == count - i - 1)
                continue;

            // If the largest value is at the front (top)
            else if (maxIndex == 0) {
                filp(num, count - i - 1);
                results[resultCnt++] = i + 1;
            }

            // If the largest value is in the middle of the current range
            else {
                // First, filp so that the largest value can come to the beginning of the array
                filp(num, maxIndex);
                results[resultCnt++] = count - maxIndex;
                // Next, filp to send the largest value last
                filp(num, count - i - 1);
                results[resultCnt++] = i + 1;
            }
        }
        results[resultCnt++] = 0;  // End of sorting

        // Output Results
        printf("(");
        printFun(num, count);
        printf(")");
        printFun(results, resultCnt);
        printf("\n");
    }
    fclose(fp);
    return 0;
}
