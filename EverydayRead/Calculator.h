#pragma once
#include <sstream>

class Calculator
{
public:
	Calculator();
	~Calculator();

	void Init();
	void Reset();

	int GetTotal() { return total; }
	std::wstring GetStr() { return resultStr; }

private:
	std::vector<char> signGroup;
	std::vector<int> numGroup;
	std::wstringstream ss;
	std::wstring resultStr;
	int total, signCount;
};

