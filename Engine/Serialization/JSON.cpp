#include "JSON.h"

#include "istreamwrapper.h"
#include "Core/Logger.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Rect.h"

#include <fstream>
#include <fmod_common.h>

namespace en::json
{
	bool Load(const std::string& filename, rapidjson::Document& document)
	{
		std::ifstream stream(filename);
		if (!stream.is_open())
		{
			// LOG("ERROR: Cannot open file %s.", filename.c_str());
			return false;
		}

		rapidjson::IStreamWrapper istream(stream);
		document.ParseStream(istream);
		if (document.IsObject() == false)
		{
			LOG("ERROR: Cannot read JSON file %s.", filename.c_str());
			return false;
		}

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, int& data)
	{
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsInt() == false)
		{
			// LOG("ERROR: Problem reading JSON data %s", name.c_str());
			return false;
		}

		data = value[name.c_str()].GetInt();

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, float& data)
	{
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsFloat() == false)
		{
			LOG("ERROR: Problem reading JSON data %s", name.c_str());
			return false;
		}

		data = value[name.c_str()].GetFloat();

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, bool& data)
	{
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsBool() == false)
		{
			// LOG("ERROR: Problem reading JSON data %s", name.c_str());
			return false;
		}

		data = value[name.c_str()].GetBool();

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, std::string& data)
	{
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsString() == false)
		{
			LOG("ERROR: Problem reading JSON data %s", name.c_str());
			return false;
		}

		data = value[name.c_str()].GetString();

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, en::Vector2& data)
	{
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 2)
		{
			// LOG("ERROR: Problem reading JSON data %s", name.c_str());
			return false;
		}

		auto& array = value[name.c_str()];

		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsFloat())
			{
				LOG("ERROR: JSON data %s is not a float", name.c_str());
				return false;
			}

			data[i] = array[i].GetFloat();
		}

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, Color& data)
	{
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 4)
		{
			// LOG("ERROR: Problem reading JSON data %s", name.c_str());
			return false;
		}

		auto& array = value[name.c_str()];

		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsInt())
			{
				LOG("ERROR: JSON data %s is not an integer", name.c_str());
				return false;
			}

			data[i] = array[i].GetInt();
		}

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, Rect& data)
	{
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 4)
		{
			// LOG("ERROR: Problem reading JSON data %s", name.c_str());
			return false;
		}

		auto& array = value[name.c_str()];

		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsInt())
			{
				LOG("ERROR: JSON data %s is not an integer", name.c_str());
				return false;
			}

			data[i] = array[i].GetInt();
		}

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data)
	{
		if (!value.HasMember(name.c_str()))
		{
			// LOG("ERROR: Problem reading JSON data %s", name.c_str());
			return false;
		}

		if (!value[name.c_str()].IsArray())
		{
			LOG("ERROR: JSON data %s is not an array", name.c_str());
			return false;
		}

		auto& array = value[name.c_str()];

		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsString())
			{
				LOG("ERROR: JSON data %s is not a string", name.c_str());
				return false;
			}

			data.push_back(array[i].GetString());
		}

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, std::vector<int>& data)
	{
		if (!value.HasMember(name.c_str()))
		{
			// LOG("ERROR: Problem reading JSON data %s", name.c_str());
			return false;
		}

		if (!value[name.c_str()].IsArray())
		{
			LOG("ERROR: JSON data %s is not an array", name.c_str());
			return false;
		}

		auto& array = value[name.c_str()];

		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsInt())
			{
				LOG("ERROR: JSON data %s is not an int", name.c_str());
				return false;
			}

			data.push_back(array[i].GetInt());
		}

		return true;
	}
}