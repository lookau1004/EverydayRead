#include "pch.h"
#include "Random.h"

Random::Random(std::vector<string>& _sentences, int _senSize) 
	: sentences(_sentences), senSize(_senSize), gen(rd()), dis(0, _senSize - 1)
{
}

Random::~Random()
{
}
