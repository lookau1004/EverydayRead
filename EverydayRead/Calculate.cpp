#include "pch.h"

// TODO : 새로운 윈도우 창에 사칙연산 퀴즈 만들기

int test()
{
	std::vector<char> signGroup;
	srand(time(NULL));

	int signCount = std::rand() % 5 + 1; // 1 ~ 5
	std::cout << signCount << std::endl;

	signGroup.resize(signCount);

	for (int i = 0; i < signCount; ++i)
	{
		int nRand = rand() % 4;

		switch (nRand)
		{
		case 0:
			signGroup[i] = '+';
			break;
		case 1:
			signGroup[i] = '-';
			break;
		case 2:
			signGroup[i] = '*';
			break;
		case 3:
			signGroup[i] = '/';
			break;
		}
	}

	std::vector<int> numGroup(signCount + 1);

	for (int i = 0; i < numGroup.size(); ++i)
	{
		int nRand = rand() % 999 + 1; // 1 ~ 999
		numGroup[i] = nRand;
	}

	int total = numGroup[0];
	std::cout << numGroup[0] << ' ';

	for (int i = 0; i < signCount; ++i)
	{
		switch (signGroup[i])
		{
		case '+':
			total += numGroup[i + 1];
			break;
		case '-':
			total -= numGroup[i + 1];
			break;
		case '*':
			total *= numGroup[i + 1];
			break;
		case '/':
			total /= numGroup[i + 1];
			break;
		}

		std::cout << signGroup[i] << ' ' << numGroup[i + 1] << ' ';
	}

	int answer;
	std::cin >> answer;

	std::cout << std::endl << total;

	return 0;
}