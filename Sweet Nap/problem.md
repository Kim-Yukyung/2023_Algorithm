## Problem
Student J likes to nap during the day, but her schedule is so busy that she doesn't have many chances to do so.
<br> Write a program to help her with the task.

## Input
The first line of each case contains integer s < 100, representing the number of scheduled appointments for that day.
<br>
<br> The next s lines contain the appointments in the format time 1 time 2 appointment,
<br> where time 1 represents the time which the appointment starts and time 2 the time it ends.
<br>
<br> All times will be in the hh:mm format;
<br> The endgint time will always be strictly after the starting time, and separated by a single space.
<br>
<br> All times will be greater than or equal of 10:00 and less than or equal to 18:00.

## Sample Input
4
<br> 10:00 12:00 Lectures
<br> 12:00 13:00 Lunch, like always
<br> 13:00 15:00 Boring lectures
<br> 16:45 17:45 Reading

## Sample Output
Day #1: The longest nap starts at 15:00 and will last for 1 hours and 45 minutes
