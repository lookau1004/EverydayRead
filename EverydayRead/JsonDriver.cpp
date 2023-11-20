#include "pch.h"
#include "JsonDriver.h"

JsonDriver::JsonDriver(std::string _inputJson) : inputJson(_inputJson)
{
	jsonData = json::parse(inputJson);
	sentences.push_back(jsonData.at("0"));
}

JsonDriver::~JsonDriver()
{
}
