#include "pch.h"
#include "JsonParse.h"

JsonParse::JsonParse()
{
}

void JsonParse::Init(std::string _inputJson, std::vector<string> _sentences, std::string _findStr)
{
	inputJson = _inputJson;
	sentences = _sentences;
	findStr = _findStr;

	jsonData = json::parse(inputJson);
	sentences = jsonData[findStr].get<std::vector<std::string>>();
}

JsonParse::~JsonParse()
{
}
