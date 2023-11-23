#include "pch.h"
#include "Random.h"

Random::Random()
{
}

Random::~Random()
{
}

int Random::GetNumber(int _senSize)
{
	senSize = _senSize;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, senSize - 1);

	return dis(gen);
}
