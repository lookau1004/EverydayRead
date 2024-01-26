#pragma once

#include <experimental/filesystem>

class DirList
{
public:
	DirList();
	~DirList();

	void Init();
	void Load();
	std::vector<std::string> GetVec();

private:
	std::vector<std::string> dirListVec;
};

