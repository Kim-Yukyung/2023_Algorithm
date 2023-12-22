## Problem
After the trip, each student's expenses are tallied and money is exchanged so that the net cost to each is the same,
<br> to within 10 won. 
<br> 
<br> Your job is to compute, from a list of expenses, the minimum amount of money that must change hands in order to equalize 
<br> (within one wond) all the students' costs.


## Input
Standard input will contain the information for several trips.
<br> Each trip consists of a line containing a positive integer n denoting the number of student on the trip.
<br> 
<br> This is followed by n lines of input, each containing the amount spent by a student in 10 wo units.
<br> 
<br> There are no more than 100 students and no student spent more than 100,000 won.
<br>
<br> A single line containing 0 follows the infromation for the last trip.

## Output
For each trip, output a line stating the total amout of money, in won units,
<br> that must be exchanged to equalize the students' costs.

## Sample Input
3
<br> 10000
<br> 20000
<br> 30000
<br> 4
<br> 15000
<br> 15010
<br> 3000
<br> 3010
<br> 0

## Sample Output
10000
<br> 11990
