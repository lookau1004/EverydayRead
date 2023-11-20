#pragma once
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JsonDriver
{
public:
	JsonDriver(std::string);
	~JsonDriver();

private:
	std::string inputJson;
	std::vector<string> sentences;
	json jsonData;
};

