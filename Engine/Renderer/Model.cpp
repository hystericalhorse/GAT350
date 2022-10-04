#include "Model.h"
#include "Core/File.h"
#include "Math/Transform.h"
#include "Math/MathUtils.h"
#include "Core/Logger.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace en
{
	Model::Model(const std::string& filename)
	{
		Load(filename);
		_radius = findRadius();
	}

	Model::Model(const std::string& filename, const en::Color& color)
	{
		Load(filename);
		_radius = findRadius();
		_color = color;
	}

	void Model::Draw(Renderer& renderer, const Vector2& position, float& angle, const Vector2& scale)
	{
		if (_points.size() == 1)
		{
			renderer.drawPoint(position, _color);
			return;
		}

		for (size_t i = 0; i < _points.size() - 1; i++)
		{
			renderer.drawLine(Vector2::rotate(_points[i] * scale, angle) + position, Vector2::rotate(_points[i + 1] * scale, angle) + position, _color);
		}
	}

	void Model::Draw(Renderer& renderer, const Transform& transform)
	{
		if (_points.empty()) return;

		Matrix3x3 mx = transform.matrix;

		if (_points.size() == 1)
		{
			renderer.drawPoint(transform.position, _color);
			return;
		}

		for (size_t i = 0; i < _points.size() - 1; i++)
		{
			renderer.drawLine(
				Vector2::rotate(_points[i] * transform.scale, radians(transform.rotation)) + transform.position,
				Vector2::rotate(_points[i + 1] * transform.scale, radians(transform.rotation)) + transform.position,
				_color
			);
		}
	}

	bool Model::Create(std::string filename, ...)
	{
		va_list args;
		va_start(args, filename);
		va_end(args);

		return Model::Load(filename);
	}

	bool Model::Load(const std::string& filename)
	{
		std::string buffer;
		if (!en::readFile(filename, buffer))
		{
			LOG("ERROR: Could not read file %s", filename.c_str());
			return false;
		}

		std::istringstream stream(buffer);
		stream >> _color;

		std::string line;
		std::getline(stream, line);

		size_t points = std::stoi(line); // get the number of points
		for (size_t i = 0; i < points; i++)
		{
			Vector2 point;

			stream >> point; // read points

			_points.push_back(point);
		}

		return true;
	}

	float Model::findRadius()
	{
		float r = 0.0f;

		for (auto& point : _points)
		{
			if (point.length() > r) r = point.length();
		}

		return r;
	}
}