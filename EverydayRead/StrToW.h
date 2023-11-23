#pragma once

#include <locale>
#include <codecvt>

class StrToW
{
public:
	StrToW();
	~StrToW();

	std::wstring Convert(std::string);

private:
};
