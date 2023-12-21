#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Time table size
#define HOUR 8  // 10:00 to 18:00 -> 8 hours
#define MINUTE 60

int main() {
    FILE* fp = fopen("Input_1.txt", "r");

    // Exception handling
    if (fp == NULL) {
        printf("Error : Cannot open the file\n");
        return -1;
    }

    int testNum = 1;  // Variable for test count
    int size = 0;  // Number of daily events

    // loop : repeat until end of file
    while (fscanf(fp, "%d", &size) != EOF) {
        fgetc(fp);
        printf("%d\n", size);

        // Time table
            /*
            * [0][0] : 10H 00M ~ 10H 01M, [0][1] : 10H 01M ~ 10H 02M
            * ...
            * [7][58] : 17H 58M ~ 17H 59M, [7][59] : 17H 59M ~ 18H 00M
            */
        bool time[HOUR][MINUTE] = { false, }; 

        for (int i = 0; i < size; i++) {
            char str[255];
            int startHour = 0, startMin = 0, endHour = 0, endMin = 0;

            fscanf(fp, "%d:%d %d:%d", &startHour, &startMin, &endHour, &endMin);
            fgets(str, sizeof(str), fp);

            // Remove newline characters at the end of a string
            if(str[strlen(str) - 1] == '\n')
                str[strlen(str) - 1] = '\0';
            printf("%d:%02d %d:%02d %s\n", startHour, startMin, endHour, endMin, str);

            // Convert start and end times to minutes for recording in a time table
            // The time table starts from 0:00, so exclude 10 hours when converting
            int start = (startHour - 10) * 60 + startMin;
            int end = (endHour - 10) * 60 + endMin;
            int row = 0, column = 0;

            // Display the schedule in the time table
            for (int j = start; j < end; j++) {
                row = j / 60;
                column = j % 60;
                time[row][column] = true;
            }
        }

        int result = 0, tmp = 0;  // result : the final result, tmp : check for consecutive times
        int resultH = 18, resultM = 0;

        // loop : get the longest nap time
        for (int i = 0; i < HOUR; i++) {
            for (int j = 0; j < MINUTE; j++) {
                // Increase 'tmp' if nap time is continuous
                if (time[i][j] == false) {
                    tmp++;
                    // Update value if 'tmp' time is longer than 'result' time
                    if (tmp > result) {
                        result = tmp;
                        resultH = i + 10;
                        resultM = j + 1;
                    }
                }
                // Change to 'tmp' 0 if nap time is not continuous
                else {
                    tmp = 0;
                }
            }
        }

        // Excluding the final results from the current time to find out what time you can take a nap
        int tempTime = resultH * 60 + resultM - result;
        resultH = tempTime / 60;
        resultM = tempTime % 60;

        // Result output
        if (result / 60 == 0)
            printf("Day #%d: the longest nap starts at %02d:%02d and will last for %d minutes.\n\n", testNum, resultH, resultM, result % 60);
        else
            printf("Day #%d: the longest nap starts at %02d:%02d and will last for %d hours and %d minutes.\n\n", testNum, resultH, resultM, result / 60, result % 60);

        testNum++;
    }
    fclose(fp);
    return 0;
}
