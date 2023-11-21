#pragma once
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JsonParse
{
public:
	JsonParse(std::string _inputJson, std::vector<string>& _sentences);
	~JsonParse();

	std::vector<string> GetVector() { return sentences; }

private:
	std::string inputJson;
	std::vector<string> &sentences;
	json jsonData;
};

