#pragma once
#include <random>

// ����
	//sentencesNum = random.GetNumber(sentences.size());				// mt19937 ���� ���
	//sentencesNum = sentencesRandom.GetRandomNum();
	//sentence = strToW.Convert(sentences[sentencesNum]);

class Random
{
public:
	Random();
	~Random();
	
	int GetNumber(int _senSize);

private:
	int senSize;	  
};

