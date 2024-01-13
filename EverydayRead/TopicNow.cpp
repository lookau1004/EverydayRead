#include "pch.h"
#include "TopicNow.h"

TopicNow::TopicNow()
{
}

TopicNow::~TopicNow()
{
}

void TopicNow::PyLoad()
{
	system("python .//python//crawler.py");
}

std::string TopicNow::GetString()
{

	string topicResult;
	ifstream file(".//python//data.json");

	if (file.is_open())
	{
		string temp;
		while (getline(file, temp))
		{
			topicResult += temp;
		}
		file.close();
	}

	return topicResult;
}
