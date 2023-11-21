#include "pch.h"
#include "GetHtml.h"

GetHtml::GetHtml(const char* _link) : link(_link)
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
}

GetHtml::~GetHtml()
{
	curl_global_cleanup();
}

size_t GetHtml::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data)
{
	data->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::string GetHtml::Load()
{
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, link);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK)
		{
			readBuffer = "curl_easy_perform() failed";
			//fprintf(stderr, "curl_easy_perform() failed: %s \n", curl_easy_strerror(res));
		}

		curl_easy_cleanup(curl);
	}

	return readBuffer;
}

