#ifndef _CUBE_MAP_TEXTURE_H
#define _CUBE_MAP_TEXTURE_H

#include "Texture.h"
#include <vector>

namespace en
{
	class CubemapTexture : public Texture
	{
	public:
		bool Create(std::string filename, ...) override;
		bool Load(const std::vector<std::string>& filenames);

	private:
		std::vector<std::string> genCubemapNames(const std::string& basename, const std::string& extension);
	};
}

#endif // _CUBE_MAP_TEXTURE_H