#pragma once
#include <random>

class Random
{
public:
	Random();
	~Random();
	
	int GetNumber(int _senSize);

private:
	int senSize;	  
};

