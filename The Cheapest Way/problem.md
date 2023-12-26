## Problem
Given an *m x n* matrix of integers, you are to write a program that computes a path of minimal weight 
<br> from left to right across the matrix.
<br> 
<br> A path starts anywhere in column 1 and consists of a sequence of steps termination in column n.
<br> 
<br> Each step consists of traveling from column *i* to column *i+1* in an adjacent row.
<br> 
<br> The first and last rows of a matrix are considered adjacent.
<br> <br> ![df64c71fbe5d47c2b828969ad4ec7885](https://github.com/Kim-Yukyung/2023_Algorithm/assets/154517645/2674b31a-fcdc-4b8a-9fa1-1e17b5ba11be)

## Input
The input consists of a sequence of matrix specifications.
<br> 
<br> Each matix consists of the row and column dimensions on a line, denoted m and n, respectively.
<br> 
<br> This is followed by m x n integers, appearing in row major order.
<br> 
<br> Integers are not restricted to being positive. 
<br> 
<br> For each specification the number of rows will be between 1 and 10 inclusive; 
<br> The number of columns will be between 1 and 100 inclusive.

## Output
Two lines should be output for each matrix specification.
<br> 
<br> The first line represents a minimal-weight path, and the second line is the cost of this minimal path.
<br> 
<br> If there is more that one path of minimal weight, the lexicographically smallest path should be output.

## Sample Input
5 6
<br> 3 4 1 2 8 6
<br> 6 1 8 2 7 4
<br> 5 9 3 9 9 5
<br> 8 4 1 3 2 6
<br> 3 7 2 8 6 4
<br> 5 6
<br> 3 4 1 2 8 6
<br> 6 1 8 2 7 4
<br> 5 9 3 9 9 5
<br> 8 4 1 3 2 6
<br> 3 7 2 1 2 3

## Sample Output
3 1 3 3 2 4
<br> 16
<br> 3 1 1 1 2 3
<br> 11
