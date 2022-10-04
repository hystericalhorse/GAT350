#ifndef _FILE_H
#define _FILE_H
#include <string>

namespace en
{
	void setPath(const std::string& pathname);
	std::string getPath();

	bool fileExists(const std::string& pathname);
	bool fileSize(const std::string& pathname, size_t& size);
	bool readFile(const std::string& pathname, std::string& buffer);
}

#endif // _FILE_H