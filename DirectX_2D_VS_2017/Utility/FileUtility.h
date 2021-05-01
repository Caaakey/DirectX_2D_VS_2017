#pragma once
#include <sys/stat.h>
#include <fstream>

class FileUtility
{
public:
	static inline bool Exists(const std::wstring& path)
	{
		std::string str = StringUtility::ConvertString(path);
		return Exists(str);
	}
	static inline bool Exists(const std::string& path)
	{
		struct stat buffer;
		return (stat(path.c_str(), &buffer) == 0);
	}
};
