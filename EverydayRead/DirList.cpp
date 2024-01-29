#include "pch.h"
#include "DirList.h"

DirList::DirList() : dirListVec(0)
{
}

DirList::~DirList()
{
}

void DirList::Init()
{
	std::experimental::filesystem::create_directory("./sources/");
}

void DirList::Load()
{
	for (const experimental::filesystem::directory_entry& entry :
		experimental::filesystem::recursive_directory_iterator(experimental::filesystem::current_path() / "sources"))
	{
		const std::string ext = entry.path().extension().string();

		if (ext == ".cpp")
		{
			dirListVec.push_back(entry.path().string());
		}
	}
}

std::vector<std::string> DirList::GetVec()
{
	return dirListVec;
}
