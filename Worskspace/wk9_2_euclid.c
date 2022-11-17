#pragma warning(disable: 4996)
#include<stdio.h>

int* extendedEuclid(int a, int b)
{
	int result[3] = { 0,0,0 };
	int* arr;
	if (b == 0)
	{
		result[0] = a;
		result[1] = 1;
		result[2] = 0;
		return result;
	}
	arr = extendedEuclid(b, a % b);
	result[0] = arr[0];
	result[1] = arr[2];
	result[2] = arr[1] - (a / b) * arr[2];

	return result;
}
void main()
{
	int* arr;
	int a, b;
	
	while (1)
	{
		scanf("%d %d", &a, &b);
		arr = extendedEuclid(a, b);
		printf("%d %d %d\n", arr[1], arr[2], arr[0]);
	}	
}

/*
4 6 

17 17

--> -1 1 2    0 1 17
*/