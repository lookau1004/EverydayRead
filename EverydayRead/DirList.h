#pragma once

#include <experimental/filesystem>

class DirList
{
public:
	DirList(std::vector<std::string>& _dirListVec);
	~DirList();
	void Load();
private:
	std::vector<std::string>& dirListVec;
};

