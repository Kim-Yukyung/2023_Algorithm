## Problem
Some people think that the bigger an elephant is, the smarter it is.
<br> 
<br> To disprove this, you want to analyze a collection of elephants and place as large a subset of elephants as possible 
<br> into a sequence whose weights are increasing but IQ's are decreasing.

## Input
The input will consist of data for a bunch of elephants, at on elephant per line terminated by the end-of file.
<br> 
<br> The data contains information on at most 1,000 elephants.
<br> 
<br> The data for each particular elephant will consist of a pair of integers:
<br> The first representing its size in kilograms and the second representing its IQ in the hundredths of IQ points.
<br> 
<br> Both integers are between 1 and 10,000.

## Output
The first ouput line should contain an integer n, the length of elephant sequence found.
<br> 
<br> The remaining n lines should each contain a single positive integer representing an elephant.
<br> 
<br> In order for the answer to be correct, n must be as large as possible.
<br> 
<br> All inequalities are strict: Weights must be strictly increasing, and IQs must be strictly decreasing.

## Example
| Input |     |     |    |Answer1|     |     |    |Answer2|     |     |
|-------|-----|-----|----|-------|-----|-----|----|-------|-----|-----|
|   1   | 50  | 100 |    |   1   | 50  | 100 |    |   1   | 50  | 100 |
|   2   | 100 | 90  |    |   2   | 100 | 90  |    |   2   | 100 | 90  |
|   3   | 150 | 180 |    |   4   | 200 | 70  |    |   5   | 250 | 70  |
|   4   | 200 | 70  |    |       |     |     |    |       |     |     |
|   5   | 250 | 70  |    |       |     |     |    |       |     |     |
|   6   | 0   |     |    |       |     |     |    |       |     |     |

## Sample Input
6008 1300
<br> 6000 2100
<br> 500 2000
<br> 1000 4000
<br> 1100 3000
<br> 6000 2000
<br> 8000 1400
<br> 6000 1200
<br> 2000 1900
<br> 0

## Sample Output
4
<br> 4
<br> 5
<br> 9
<br> 7
