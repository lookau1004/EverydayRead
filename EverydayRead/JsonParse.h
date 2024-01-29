#pragma once
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JsonParse
{
public:
	JsonParse();
	~JsonParse();

	void Init(std::string _inputJson, std::vector<string> _sentences, std::string _findStr);
	std::vector<string> GetVector() { return sentences; }

private:
	std::string inputJson, findStr;
	std::vector<std::string> sentences;
	json jsonData;
};

