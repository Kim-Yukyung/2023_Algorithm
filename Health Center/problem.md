## Problem
Choose the location of the new health center so as to reduce the distance to the nearest center from the houses 
<br> of the farthest-served residents.
<br> 
<br> The city has up to 500 intersections, connected by road segments of various lengths.
<br> 
<br> No more than 20 road segments intersect at a given intersection.
<br> 
<br> The locations of houses and health centers alike are considered to be at intersections.
<br> 
<br> Furthermore, we assume that there is at least one house associated with every intersection.

## Input
The first line of input contains two positive integers: the number of existing health centers f(f <= 100) and 
<br> the number of intersections i (i <= 500).
<br> 
<br> Intersections are numbered from 1 to i consecutively.
<br> 
<br> The f lines follow, each containing the intersection number at which an existing health center is found.
<br> 
<br> A number of i lines follow, each containing three positive integers: the number of an intersection, 
<br> the number of a different intersection, and the length of the road segment connecting the intersections.
<br> 
<br> All road segments are two-way, and there will exist a route between any pair of intersections.

## Output
For each test case, output the lowest intersection number at which a new health center can be built so as to minimize 
<br> the maximum distance from any intersection to its nearest health center.
<br> 
<br> Separate the output of each two consecutive cases by a blank line.

## Sample Input
1 6
<br> 2
<br> 1 2 10
<br> 2 3 10
<br> 3 4 10
<br> 4 5 10
<br> 5 6 10
<br> 6 1 10

## Sample Output
5
