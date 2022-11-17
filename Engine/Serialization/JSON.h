#ifndef _JSON_H
#define _JSON_H

#include "document.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>

#define READ_DATA(value, data) en::json::Get(value, #data, data)
#define READ_NAME_DATA(value, name, data) en::json::Get(value, name, data)

namespace en
{
	struct Vector2;
	struct Color;
	struct Rect;

	namespace json
	{
		bool Load(const std::string& filename, rapidjson::Document& document);

		bool Get(const rapidjson::Value& value, const std::string& name, int& data);
		bool Get(const rapidjson::Value& value, const std::string& name, float& data);
		bool Get(const rapidjson::Value& value, const std::string& name, bool& data);
		bool Get(const rapidjson::Value& value, const std::string& name, std::string& data);
		bool Get(const rapidjson::Value& value, const std::string& name, en::Vector2& data);
		bool Get(const rapidjson::Value& value, const std::string& name, en::Color& data);
		bool Get(const rapidjson::Value& value, const std::string& name, en::Rect& data);
		bool Get(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data);
		bool Get(const rapidjson::Value& value, const std::string& name, std::vector<int>& data);
		bool Get(const rapidjson::Value& value, const std::string& name, glm::vec2& data);
		bool Get(const rapidjson::Value& value, const std::string& name, glm::vec3& data);
		bool Get(const rapidjson::Value& value, const std::string& name, glm::vec4& data);
	}
}

#endif // _JSON_H