#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_STRING_LEN 10000
#define MAX_TARGET_LEN 100

/// <summary>
/// Algorithm Description (dp[string][target])
/// 1. If one character is the same, can select this character and move on, or can skip without selecting it.
///		If there are strings ab(1)b(2)b(3), b(1)b(2) and currently b(1)==b(1)
///		1) Compare ab(1)b(2), b(1)b(2) --> Select overlapping characters
///		2) Compare ab(1)b(2), b(1) --> Do not select overlapping characters
///		==> The sum of the selected and unselected cases is the maximum number of overlapping sequences so far.
///		==> dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
/// 2. If the characters are different, the maximum length to date is equal to the length from now to -1.
///		If there are abc and ac, a and a overlap, so the maximum number so far is 1.
///		ab, ac -> Because b and c are different letters, the maximum length is 1 -> a, the same as the length of a.
///		==> dp[i][j] = dp[i-1][j]
/// </summary>
unsigned int findDistance(char str[], char target[], int lenStr, int lenTarget) {
	unsigned int* dp = (unsigned int*)malloc(sizeof(unsigned int) * (lenStr + 1));

	if (dp == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}

	// if : The string in the target is longer, the number is 0.
	if (lenStr < lenTarget) {
		free(dp);
		return 0;
	}

	unsigned int weight = 1;  // Initialization : Empty string -> Count to empty string 1

	for (int i = 0; i < lenTarget; i++) {
		for (int j = 1; j < lenStr + 1; j++) {
			unsigned int prev = weight;  // Save previous weight values

			// Initialization : String -> Count to empty string is 1
			if (i == 0)
				dp[j] = 1;

			// Initialization : Empty string -> Count to string is 0
			if (j == 1)
				dp[j - 1] = 0;

			weight = dp[j];  // Save Current Weight Value

			// if : If the current character and the target character are the same
			if (str[j - 1] == target[i])
				dp[j] = prev + dp[j - 1];
			else
				dp[j] = dp[j - 1];
		}
		weight = dp[0];
	}

	unsigned int result = dp[lenStr];

	free(dp);
	return result;
}

int main() {
	FILE* fp = fopen("Input_5.txt", "r");

	if (fp == NULL) {
		printf("Cannot open file\n");
		return -1;
	}

	int size = 0;
	fscanf(fp, "%d", &size);
	fgetc(fp);

	for (int i = 0; i < size; i++) {
		char* str = (char*)malloc(sizeof(char) * (MAX_STRING_LEN + 10));
		char* target = (char*)malloc(sizeof(char) * (MAX_TARGET_LEN + 10));

		if (str == NULL || target == NULL) {
			printf("Memory allocation failed\n");
			return -1;
		}

		fgets(str, MAX_STRING_LEN + 10, fp);
		fgets(target, MAX_TARGET_LEN + 10, fp);

		// if : Delete '\n' characters
		if (str[strlen(str) - 1] == '\n')
			str[strlen(str) - 1] = '\0';
		if (target[strlen(target) - 1] == '\n')
			target[strlen(target) - 1] = '\0';

		int lenStr = 0, lenTarget = 0;
		bool hasError = false;

		// loop : Error in input if capital letters exist
		for (int i = 0; str[i] != '\0'; i++) {
			lenStr++;
			if (isupper(str[i])) {
				printf("Error : Type capital letters\n");
				hasError = true;
				break;
			}
		}
		for (int i = 0; target[i] != '\0'; i++) {
			lenTarget++;
			if (isupper(target[i])) {
				printf("Error : Type capital letters\n");
				hasError = true;
				break;
			}
		}

		// if : Input error if input maximum length is exceeded
		if (lenStr > MAX_STRING_LEN || lenTarget > MAX_TARGET_LEN) {
			printf("Error : Input Length Exceeded\n");
			return -1;;
		}
		else if (hasError)
			return -1;
		else 
			printf("%d\n", findDistance(str, target, lenStr, lenTarget));

		free(str);
		free(target);
	}

	fclose(fp);
	return 0;
}
