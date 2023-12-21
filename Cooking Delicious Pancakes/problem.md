## Problem
Sorting a stack is done by a sequence of pancake **flips**.
<br>
<br> A flip consists of inserting a spatula between two pancakes in a stack and flipping (reversing)
<br> all the pancakes on the spatula (reversing the sub-stack).

## Input
The input consist of a sequence of stacks of pancakes.
<br>
<br> Each stack will consist of between 1 and 30 pancakes and each pancake will have an integer diameter between 1 and 10.
<br>
<br> Each stack is given as a single line of input with the top pancake on a stack appearing first on a line,
<br> the bottom pancake appearing last, and all pancakes separated by a space.

## Output
For each stack of pancakes, your program should echo the original stack on one line, followed by a sequence of flips 
<br> that results in sorting the stack of pancakes so that the largest pancake is on the bottom and the smallest on top.
<br>
<br> The sequence of flips for each stack should be terminated by a 0, indicating no more flips necessary.
<br>
<br> Once a stack is sorted, no more flips should be made.

## Example
|   | filp(1) |   | filp(2) |   |
|---|---------|---|---------|---|
| 5 |         | 4 |         | 1 |
| 1 |         | 3 |         | 2 |
| 2 |         | 2 |         | 3 |
| 3 |         | 1 |         | 4 |
| 4 |         | 5 |         | 5 |

## Sample Input
1 2 3 4
<br>5 4 3
<br>5 1 2 3 4

## Sample Output
1 2 3 4(1 2 3 4)0
<br>5 4 3(3 4 5) 1 0
<br>5 1 2 3 4(1 2 3 4 5)1 2 0
