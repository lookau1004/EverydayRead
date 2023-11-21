#include "pch.h"
#include "JsonParse.h"

JsonParse::JsonParse(std::string _inputJson, std::vector<string>& _sentences)
	: inputJson(_inputJson), sentences(_sentences)
{
	jsonData = json::parse(inputJson);
	sentences = jsonData["cppguidelines"].get<std::vector<std::string>>();
}

JsonParse::~JsonParse()
{
}
