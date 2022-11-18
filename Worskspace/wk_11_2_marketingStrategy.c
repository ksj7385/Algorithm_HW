#pragma warning(disable: 4996)
//ú°Öõû¿Îù  û¿Ññ!!

#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include<stdbool.h>

#define MAX 10000
#define INF 987654321


struct Point {
	double x, y;
}ar[MAX], tmp[MAX / 2];

bool increaseX(struct Point  a, struct Point b) 
{
	return a.x < b.x;
}

bool increaseY(struct Point a, struct Point b) 
{
	return a.y < b.y;
}

double MinDis(int L, int R) {
	if (R - L == 1)
		return INF;
	if (R - L == 2) 
	{
		double X = ar[L + 1].x - ar[L].x, Y = ar[L + 1].y - ar[L].y;
		return sqrt(X * X + Y * Y);
	}

	int mid = (L + R) / 2;
	double Min = min(MinDis(L, mid), MinDis(mid + 1, R));
	int tmp_n = 0;

	for (int i = L; i < R; i++)
		if (ar[i].x > ar[mid].x - Min && ar[i].x < ar[mid].x + Min)
			tmp[tmp_n++] = ar[i];

	qsort(tmp, sizeof(struct Point) * tmp_n, sizeof(struct Point), increaseY);


	for (int i = 0; i < tmp_n - 1; i++)
		for (int j = i + 1; j < tmp_n; j++) 
		{
			if (tmp[j].x - tmp[i].x >= Min)
				break;
			double X = tmp[j].x - tmp[i].x, Y = tmp[j].y - tmp[i].y;
			Min = min(Min, sqrt(X * X + Y * Y));
		}
	return Min;
}

int main() {
	int N;
	while (true) 
	{
		scanf("%d", &N);
		if (N == 0)//The input is terminated by a set whose N =0,
			break;
		for (int i = 0; i < N; i++) 
			scanf("%lf %lf", &ar[i].x, &ar[i].y);

		qsort(ar, sizeof(struct Point) * N, sizeof(struct Point), increaseX); //sort input data by x-coordinate.
		double ans = MinDis(0, N);

		if (ans > 10000)
			printf("\nINFINITY\n");
		else 
			printf("\n%.2lf\n", ans);
	}
	return 0;
}
/*
3
0 0
10000 10000
20000 20000
5
0 2
6 67
43 71
39 107
189 140
0
*/