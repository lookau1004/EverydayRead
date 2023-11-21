#include "pch.h"
#include "StrToW.h"

StrToW::StrToW()
{
}

StrToW::~StrToW()
{
}

std::wstring StrToW::Convert(std::string s)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(s);
}
