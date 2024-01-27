#include <iostream>
#define N 5

int main()
{

	int scores[N] = { 1, 3, 4, 3, 5 };
	int indexes[N + 1] = { 0, };
	int max = INT_MIN;
	int mode = 0;

	for (int i = 0; i < N; i++)
	{
		indexes[scores[i]]++;
	}
	for (int i = 0; i < N + 1; i++)
	{
		if (indexes[i] > max)
		{
			max = indexes[i];
			mode = i;
		}
	}

	printf("최빈값: %d -> %d번 나타남\n", mode, max);
}
1
1
1
1
1

1
1

1
1
1
1
1
1
1
1
1
1
1
1

1
1

1
1
1
1
1
1
1
1
1
1
1
1
1

1
1

1
1
1
1
1
1
1
1
1
1
1
1
1

1
1

1
1
1
1
1
1
1
1
1
1
1
1
1

1
1

1
1
1
1
1
1
1
1
1
1
1
1

1
1

1
1
1
1
1
1
1
1
1
1
1
1

1
1

1
1
1
1
1
1
1
1
1
1
1
1

1
1

1
1
1
1
1
1
1

1
1

1
1
