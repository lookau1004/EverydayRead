#include "pch.h"
#include "Calculator.h"

Calculator::Calculator()
{
}

Calculator::~Calculator()
{
}

void Calculator::Init()
{
	srand(time(NULL));

	signCount = std::rand() % 2 + 1; // 1 ~ 2 부호 개수
	signGroup.resize(signCount);
	numGroup.resize(signCount + 1);

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

	for (int i = 0; i < numGroup.size(); ++i)
	{
		int nRand = rand() % 999 + 1; // 1 ~ 999
		numGroup[i] = nRand;
	}

	total = numGroup[0];
	ss << numGroup[0];

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

		ss << L" " << signGroup[i] << L" " << numGroup[i + 1];
	}

	resultStr = ss.str();
}

void Calculator::Reset()
{
	ss.str(L"");
}
