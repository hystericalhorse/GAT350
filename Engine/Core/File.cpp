#include "File.h"
#include "Logger.h"
#include <filesystem>
#include <fstream>

namespace en
{
	void setPath(const std::string& pathname)
	{
		std::filesystem::current_path(pathname);
	}

	std::string getPath()
	{
		return std::filesystem::current_path().string();
	}

	bool fileExists(const std::string& pathname)
	{
		return std::filesystem::exists(pathname);
	}

	bool fileSize(const std::string& pathname, size_t& size)
	{
		if (!fileExists(pathname)) return false;
		size = std::filesystem::file_size(pathname);

		return true;
	}

	bool readFile(const std::string& pathname, std::string& buffer)
	{
		if (!fileExists(pathname))
		{
			LOG("ERROR: Could not read file %s", pathname.c_str());
			return false;
		}

		size_t size;
		fileSize(pathname, size);
		buffer.resize(size);

		std::ifstream fstream(pathname);
		fstream.read(buffer.data(), size);
		fstream.close();

		return true;
	}
}