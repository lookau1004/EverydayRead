#pragma once
#include <curl/curl.h>

class CurlDriver
{
public:
	CurlDriver(const char*);
	~CurlDriver();

	string GetResult() { return readBuffer; }
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data);

	std::string Load();

private:
	CURL* curl;
	CURLcode res;
	std::string readBuffer;
	const char *link;
};

