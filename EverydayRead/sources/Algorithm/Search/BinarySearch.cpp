#include <iostream>

int main()
{
	int search;

	int data[] = { 1, 3, 5, 7, 9 };
	int arrayCount = sizeof(data) / sizeof(int);
	bool isFind = false;
	int FindIndex = -1;

	int low = 0;
	int high = arrayCount - 1;

	std::cin >> search;

	while (low <= high)
	{
		int mid = (low + high) / 2;

		if (data[mid] == search)
		{
			isFind = true;
			FindIndex = mid;
			break;
		}
		if (data[mid] > search)
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}

	if (isFind)
		std::cout << search << "을 " << FindIndex << "에서 찾았습니다";
	else
		std::cout << "찾지 못했습니다";


}