#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX 30 //You can change it so that it show various results


#define INF 98765432141
#define PI 3.141592
#define RADIANPI 180
#define CCW 1
#define CW -1
#define ST 0

//stack function
typedef struct Stack
{
    double x;
    double y;
    double angle;
}stack;
//global vars
int top = -1;//for indexing stack
int n = 0;//for inputSequence
stack xVector = { INF, 0 }; //for caluculating angle

int isFull(stack* s)
{
    if (top >= MAX - 1)
        return 1;
    else
        return 0;
}
int isEmpty(stack* s)
{
    if (top < -1)
        return 1;
    else
        return 0;
}
stack pop(stack* s)
{
    if (isEmpty(s))
        printf("Stack empty\n");//defensive code
    return s[top--];
}
void push(stack* s, stack data)
{
    if (isFull(s))
        printf("Stack full\n");//defensive code
    top++;
    s[top].x = data.x;
    s[top].y = data.y;
    s[top].angle = data.angle;

}
void cleanStack(stack* s)
{
    for (int i = 0; i < MAX; i++)
    {
        s[i].x = 0;
        s[i].y = 0;
        s[i].angle = 0;
        top = -1;
    }
}
//helper functions
double innerProduct(stack u, stack v)
{
    double innerProduct = 0;
    innerProduct = u.x * v.x + u.y * v.y;
    return innerProduct;
}
double absoulute(double n)
{
    return fabs(n);
}
double distanceFrom0(stack s)
{
    double distance = sqrt(s.x * s.x + s.y * s.y);
    return distance;
}
double distance(stack u, stack v)
{
    double distance = sqrt(pow((u.x - v.x), 2) + pow((u.y - v.y), 2));
    return distance;
}
void printList(stack* s, int col)
{
    for (int i = 0; i < col; i++)
        printf("%lf %lf\n", s[i].x, s[i].y);
}
void printConvelHull(stack* s)
{
    for (int i = 0; i < top + 1; i++)
    {
        printf("convexHull %lf %lf %lf\n", s[i].x, s[i].y, s[i].angle);
    }
}
void printStack(stack* s, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("stack level %d %lf %lf %lf\n", i, s[i].x, s[i].y, s[i].angle);
    }
}
void bubbleSort(stack* s, int col)
{
    double tmp1, tmp2, tmp3;
    for (int i = col - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (s[j].angle > s[j + 1].angle)
            {
                tmp1 = s[j].x;
                tmp2 = s[j].y;
                tmp3 = s[j].angle;

                s[j].x = s[j + 1].x;
                s[j].y = s[j + 1].y;
                s[j].angle = s[j + 1].angle;

                s[j + 1].x = tmp1;
                s[j + 1].y = tmp2;
                s[j + 1].angle = tmp3;

            }
        }
    }
}
double isCCW(stack p, stack q, stack r)
{

    //external product
    double x1, x2, x3, y1, y2, y3;
    x1 = p.x, x2 = q.x, x3 = r.x;
    y1 = p.y, y2 = q.y, y3 = r.y;

    double result = x1 * y2 + x2 * y3 + x3 * y1 - (x2 * y1 + x3 * y2 + x1 * y3);

    if (result > 0) { printf("ccw\n"); return CCW; }
    else if (result < 0) { printf("cw\n"); return CW; }
    else { printf("st"); return ST; }
}

// int isIntersect(double a[2], double b[2], double c[2], double d[2])
// {
//     double tmp1 = isCCW(a,b,c)*isCCW(a,b,d);
//     double tmp2 = isCCW(c,d,a)*isCCW(c,d,a); 
//     if((tmp1 <= 0) && (tmp2 <= 0))
//         return 1;
//     return 0;
// }
double angle(stack u, stack v)
{
    double ip = innerProduct(u, v);
    double uDistance = distanceFrom0(u);
    double vDistance = distanceFrom0(v);

    double angle = acos(ip / (uDistance * vDistance));
    angle = angle * RADIANPI / PI;//radian to angle
    if (u.x < 0 && u.y < 0) //3th page
        angle += 90;
    else if (u.x > 0 && u.y < 0)//4th page
        angle += 270;
    return angle;
}
double stackDistance(stack* s)
{
    double result = 0.0;
    for (int i = 0; i < top; i++)
    {
        result += distance(s[i], s[i + 1]);
    }
    result += distance(s[top], s[0]);
    return result;
}
stack* graham(stack* s, int col, int row)
{
    //initialize 
    stack convexHull[MAX];
    //let P0 be the point with the minimum y-cordinate
    stack p0;
    p0.x = 0;
    p0.y = 0;

    //for (int i = 0; i < col; i++)
    //{
    //    if (s[i].y < p0.y)//find minimum y-cordinate
    //    {
    //        p0.x = s[i].x;
    //        p0.y = s[i].y;
    //    }
    //    else if (s[i].y == p0.y)//when y-cordinate same, then take the left most one
    //    {
    //        if (s[i].x < p0.x)
    //        {
    //            p0.x = s[i].x;
    //            p0.y = s[i].y;
    //        }
    //    }
    //}
    //let <P1,...,Pm> be the remaining points in Q, sorted by the angle in ccw order around p0
    stack tmp;
    for (int i = 0; i < col; i++)
    {
        tmp.x = s[i].x - p0.x; //Vector P0->s[i]
        tmp.y = s[i].y - p0.y;
        if (tmp.x == 0 && tmp.y == 0) //Angle between p0. So, p0's angle is 0
        {
            s[i].angle = 0;
            continue;
        }
        s[i].angle = angle(tmp, xVector);
    }
    bubbleSort(s, col); //sort stack by angle 

    //Push stacks into initial three points
    push(convexHull, s[0]);
    push(convexHull, s[1]);
    push(convexHull, s[2]);

    for (int i = 3; i < col; i++)
    {

        while (1)
        {
            //left turn or p0(p0 must to be included)
            if (isCCW(convexHull[top - 1], convexHull[top], s[i]) == CCW || (convexHull[top].x == 0 && convexHull[top].y == 0))
                break;
            pop(convexHull);
        }
        push(convexHull, s[i]); 
    }
    printf("Length is %0.2lf\n", round((stackDistance(convexHull) + 2) * 100) / 100); //two extra meters and ceil rounding at third decimal place
    return s;//returns convex hull
}
void inputByUser(stack* input)
{
    scanf("%d", &n); //Using global var
    for (int i = 0; i < n; i++)
    {
        scanf("%lf %lf", &input[i].x, &input[i].y);
    }
    input[n].x = 0;
    input[n].y = 0;
}

int main()
{
    stack input[MAX];

    /*****Random test*****/

    /*srand(time(NULL));
    for(int i = 0; i < MAX; i++)
    {
        input[i].x = rand() % MAX - MAX/2;
        input[i].y = rand() % MAX - MAX/2;
    }
    stack *result;
    printList(input, MAX);
    graham(input, MAX, 2);*/
    /*********************/

   /******User input******/
    int times = 0;
    scanf("%d", &times);
    for (int i = 0; i < times; i++)
    {
        inputByUser(input);
        graham(input, n + 1, 2);//graham(struct Stack stack, stack size + 1, count of dimension)
        //The reason size n + 1 is that the program will add fixed vector(0,0)
        //returns convex hull
        cleanStack(input);
    }
    /*********************/
    return 0;
}
/*
5
4
1.0 1.0
-1.0 1.0
-1.0 -1.0
1.0 -1.0

-- > 10.83
*/