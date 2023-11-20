#include "pch.h"
#include "JsonDriver.h"

JsonDriver::JsonDriver(std::string _inputJson) : inputJson(_inputJson)
{
	jsonData = json::parse(inputJson);
	sentences = jsonData["cppguidelines"].get<std::vector<std::string>>();
}

JsonDriver::~JsonDriver()
{
}
