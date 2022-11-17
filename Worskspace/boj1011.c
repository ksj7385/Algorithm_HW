#pragma warning(disable: 4996)
#pragma warning(disable: 6031) 
#include<stdio.h>
#include<stdlib.h>

int f(int s, int d)
{
	int count = 0;
	while (d > s) 
	{
		count++;
		s += count; 
		d -= count;
	}
	
	return s >= d + count ? 2 * count - 1 : 2 * count;

}

int main()
{
	int times;//test tims
	int s, d;//start point, destination point

	

	scanf("%d", &times);
	int* result = (int*)malloc(sizeof(int) * times);
	
	//input sequence
	for (int i = 0; i < times; i++)
	{
		scanf("%d %d", &s, &d);
		result[i] = f(s, d);
	}

	//output sequence
	for (int i = 0; i < times; i++)
	{
		printf("%d\n", result[i]);
	}
	return 0;
}