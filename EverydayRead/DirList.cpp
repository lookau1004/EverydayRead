#include "pch.h"
#include "DirList.h"

DirList::DirList(std::vector<std::string>& _dirListVec) : dirListVec(_dirListVec)
{
	std::experimental::filesystem::create_directory("./sources/");
}

DirList::~DirList()
{
}

void DirList::Load()
{
	for (const experimental::filesystem::directory_entry& entry :
		experimental::filesystem::recursive_directory_iterator(experimental::filesystem::current_path() / "sources"))
	{
		const std::string ext = entry.path().extension().u8string();

		if (ext == ".cpp")
		{
			std::cout << entry.path();
			dirListVec.push_back(entry.path().u8string());
		}
	}
}
