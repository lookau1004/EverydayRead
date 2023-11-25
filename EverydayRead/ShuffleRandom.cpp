#include "pch.h"
#include "ShuffleRandom.h"

ShuffleRandom::ShuffleRandom()
{
}

ShuffleRandom::~ShuffleRandom()
{
}

void ShuffleRandom::Init(int _size)
{
	size = _size;
	suffleWithSize.resize(size);

	for (int i = 0; i < size; i++)
	{
		suffleWithSize[i] = i;
	}

	srand(time(0));
	std::random_shuffle(suffleWithSize.begin(), suffleWithSize.end());
}

int ShuffleRandom::GetRandomNum()
{

	if (count == size)
	{
		count = 0;
	}
	return suffleWithSize[count++];
}

void ShuffleRandom::SetCount(int n)
{
	count = n;
}

int ShuffleRandom::GetCount()
{
	return count;
}

int ShuffleRandom::GetCountDigits()
{
	std::string s = to_string(count);

	return s.size();
}
