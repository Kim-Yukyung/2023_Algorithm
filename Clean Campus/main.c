#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct POINT {
    double x;
    double y;
}Point;

typedef struct STACK {
    Point p;
    struct STACK* next;
}Stack;

Point p0;  // Variable: Represent the reference point

// Function: Swap two points
void swap(Point* x, Point* y) {
    Point temp = *x;
    *x = *y;
    *y = temp;
}

// Function: Return the index of the point that is lowest
int startPoint(Point* points, int size) {
    int minIdx = 0;

    for (int i = 1; i < size; i++) {
        // If the current point's y-value is less than the minimum y-value found so far
        // or if the y-values are the same but the x-value is smaller, update
        if ((points[i].y < points[minIdx].y) ||
            (points[i].y == points[minIdx].y && points[i].x < points[minIdx].x)) {
            minIdx = i;
        }
    }

    return minIdx;
}

// Function: Calculate the distance between two points
double distance(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Function: Returns the orientation of three points' angles
// Positive: Counterclockwise direction, Negative: Clockwise direction, 0: Collinear
double clockwise(Point p1, Point p2, Point p3)
{
    return ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
}

/// <summary>
///     Comparison function to be passed to the 'qsort' function
///     Sorts in counterclockwise direction with respect to the reference point p0
///     If the angles are equal, sort based on distance in ascending order
/// </summary>
/// <returns>
///     If the angle is positive, it means the angle between two points is counterclockwise
///     -> return -1 (maintain the order)
///     If the angle is negative, it means the angle between two points is clockwise
///     -> return 1 (change the order)
/// </returns>
int compare(const void* a, const void* b)
{
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;

    int angle = clockwise(p0, *p1, *p2);
    // If the two points are collinear
    if (angle == 0)
        // Sort in ascending order based on distance
        return (distance(p0, *p1) < distance(p0, *p2)) ? -1 : 1;

    return (angle > 0) ? -1 : 1;
}

// Function: Add an element to the stack
void push(Stack** stack, Point p) {
    Stack* newNode = (Stack*)malloc(sizeof(Stack));

    if (newNode == NULL) {
        printf("Fail memory allocated\n");
        exit(1);
    }

    newNode->p = p;
    newNode->next = *stack;
    *stack = newNode;
}

// Function: Remove an element from the stack and return it
Point pop(Stack** stack) {
    if (*stack == NULL) {
        printf("Error: Stack is empty\n");
        exit(1);
    }

    Stack* top = *stack;
    Point popped = top->p;
    *stack = top->next;
    free(top);

    return popped;
}

// Function: Return the size of the stack
int getStackSize(Stack* stack) {
    int cnt = 0;
    Stack* cur = stack;

    while (cur != NULL) {
        cnt++;
        cur = cur->next;
    }

    return cnt;
}

// Function: Finds the convex hull using Graham's Scan algorithm
void grahamScan(Stack** stack, Point* point, int size) {
    // If the number of points is less than 3, add all points to the stack and terminate the function
    if (size < 3) {
        for (int i = 0; i < size; i++)
            push(stack, point[i]);
        return;
    }

    push(stack, point[0]); push(stack, point[1]); push(stack, point[2]);

    for (int i = 3; i < size; i++) {
        // loop: If there are two or more points in the stack, and the angle is not counterclockwise
        while (getStackSize(*stack) >= 2 && clockwise((*stack)->next->p, (*stack)->p, point[i]) <= 0) {
            pop(stack);  // Remove from the stack
        }
        push(stack, point[i]);
    }
}

// Function: Calculate the desired perimeter length from the final result using convex hull
double calculateDistance(Stack* convexHull) {
    double totalDistance = 0.0;

    Point center = { 0.0, 0.0 };
    Point startPoint = convexHull->p;
    Point prevPoint = convexHull->p;

    // Initialize a variable to store the distance to the nearest point from the origin
    double closestDistance = distance(startPoint, center);

    Stack* cur = convexHull->next;
    // loop: Traverse the stack and calculate the perimeter
    while (cur != NULL) {
        double curDistance = distance(cur->p, center);

        // Update if the current distance is shorter than the shortest distance
        if (curDistance < closestDistance)
            closestDistance = curDistance;

        // Add the distance between the previous and current point to the total perimeter
        totalDistance += distance(cur->p, prevPoint);

        prevPoint = cur->p;
        cur = cur->next;
    }

    /*
    * if: Convex hull has fewer than 3 points,
    *   If 1 point: Return round-trip distance to that point.
    *   If 2 points: Return the sum of distances between the two points and from each point to the origin
    * else:
    *   Add distance between first and last points
    *   Add distance between origin and closest point, return final length
    */
    if (getStackSize(convexHull) < 3) {
        return  (totalDistance + (distance(center, startPoint) + distance(center, prevPoint)));
    }
    else {
        totalDistance += distance(startPoint, prevPoint);
        return (totalDistance + closestDistance * 2);
    }
}

int main() {
    FILE* fp = fopen("Input_1.txt", "r");

    if (fp == NULL) {
        printf("Cannot open file\n");
        return -1;
    }

    int size = 0;
    fscanf(fp, "%d", &size);

    // If the input size exceeds computationally feasible bounds or fails to meet the problem conditions
    if (size < 1 || size > 100) {
        printf("Error: Input Size\n");
        fclose(fp);
        return -1;
    }

    Point* points = (Point*)malloc(sizeof(Point) * size);

    if (points == NULL) {
        printf("Fail memory allocated\n");
        fclose(fp);
        return -1;
    }

    for (int i = 0; i < size; i++) {
        fscanf(fp, "%lf %lf", &points[i].x, &points[i].y);
    }

    // Setting a reference point
    int startIndex = startPoint(points, size);
    p0 = points[startIndex];
    swap(&points[0], &points[startIndex]);  // Change the reference point to the first 

    // Sort points counterclockwise excluding the reference point
    qsort(&points[1], size - 1, sizeof(Point), compare);

    Stack* head = NULL;
    grahamScan(&head, points, size);

    // Result Output
    printf("%.2lf\n", calculateDistance(head));

    // Free the memory allocated
    free(points);
    while (head != NULL) {
        Stack* temp = head;
        head = head->next;
        free(temp);
    }
    fclose(fp);

    return 0;
}
