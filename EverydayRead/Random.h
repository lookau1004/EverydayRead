#pragma once
#include <random>

class Random
{
public:
	Random(std::vector<string>& _sentences, int _senSize);
	~Random();

	std::string GetSentence() { return sentences[dis(gen)]; }

private:
	int senSize;

	std::vector<string>& sentences;

	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<int> dis;
};

