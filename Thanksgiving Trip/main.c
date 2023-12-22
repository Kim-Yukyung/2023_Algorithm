#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/// <summary>
/// Find the average of the money students pay, calculate the desired result.
/// 1. It distinguishes the amount paid by students based on the average.
///		-- Why it's based on the average : To divide all values equally, all amounts must be adjusted close to the average.
/// 2. If pay less than the average, sum the insufficient amount in 'resultSum1', and if pay the same or more, sum the excess amount in 'resultSum2'.
///		-- The reason for distinguishing the two values : Because it is not accurately matched to the average, but adjusted in units of 10 won.
/// 3. Returns a smaller value among them.
///		-- The reason for returning small values: Because converges on the average if only a small amount is transferred between insufficient or excessive money.
/// </summary>
/// <param name="money">Array of students saved the amount of money</param>
/// <param name="sum">The total amount of money</param>
/// <param name="size">Number of inputs</param>
/// <returns>Minimum moving amount</returns>

double findMinimum(int * money, int sum, int size) {
	// Round to match to the nearest unit of 10 won.
	double average = round((double)sum / size / 10) * 10;

	double resultSum1 = 0;
	double resultSum2 = 0;

	for (int i = 0; i < size; i++) {
		// If paid less than the average amount
		if (money[i] < average)
			resultSum1 += (average - (double)money[i]);
		// If paid the same or more than the average amount
		else
			resultSum2 += ((double)money[i] - average);
	}

	return resultSum1 < resultSum2 ? resultSum1 : resultSum2;
}

int main() {
	FILE* fp = fopen("Input_1.txt", "r");

	// Exception handling
	if (fp == NULL) {
		printf("Error : Cannot file open\n");
		return -1;
	}
	
	int size = 0;

	while (fscanf(fp, "%d", &size) != EOF) {
		printf("%d\n", size);
		if (size == 0)
			break;

		// Exception handling : If the number of inputs is 100 or more
		bool flagSize = true;
		if (size >= 100)
			flagSize = false;

		int* money = (int*)malloc(sizeof(int) * size);
		
		// Exception handling
		if (money == NULL) {
			printf("Error : Fail to allocate memory\n");
			return -1;
		}

		int sum = 0;
		bool flagRange = true;
		
		for (int i = 0; i < size; i++) {
			fscanf(fp, "%d", &money[i]);

			if (money[i] >= 100000)
				flagRange = false;

			// Input Number Output
			printf("%d\n", money[i]);

			sum += money[i];
		}

		// Result Output
		if (flagSize == false || flagRange == false) {
			if (flagSize == false) {
				printf("Error : Input Size\n");
			}
			if (flagRange == false) {
				printf("Error : Input Range\n");
			}
		}
		else 
			printf("$%.2lf\n", findMinimum(money, sum, size));

		free(money);
	}

	fclose(fp);
	return 0;
}
