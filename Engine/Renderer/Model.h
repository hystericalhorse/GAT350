#ifndef _MODEL_H
#define _MODEL_H

#include "Renderer.h"
#include "Resource/Resource.h"
#include "Renderer.h" 
#include "VertexBuffer.h" 
#include "Math/MathUtils.h" 

#include <assimp/Importer.hpp> 
#include <assimp/scene.h> 
#include <assimp/postprocess.h>

#include <vector>
#include <string>

namespace en
{
	class Model : public Resource
	{
	public:

		struct vertex
		{
			glm::vec3 position;	/* 0 */
			glm::vec2 uv;		/* 1 */
			glm::vec3 normal;	/* 2 */
		};

	public:
		Model() = default;
		Model(const std::vector<en::Vector2>& points, const en::Color& color)
			: _points{ points }, _color{color}
		{}
		Model(const std::string& filename);
		Model(const std::string& filename, const en::Color& color);
		~Model() = default;

		void Draw(Renderer& renderer, const Vector2& position, float& angle, const Vector2& scale = Vector2{1, 1});
		void Draw(Renderer& renderer, const Transform& transform);
		bool Create(std::string filename, ...) override;
		bool Load(const std::string& filename);
		float findRadius();

		Color& getColor() { return _color; }
		void setColor(const en::Color& color) { _color = color; }
		float getRadius() { return _radius; }
		
		VertexBuffer _vertexBuffer;
	private:

		void ProcessNode(aiNode* node, const aiScene* scene);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene);

		en::Color _color {255, 255, 255, 255};
		std::vector<en::Vector2> _points;
		std::string _name;

		float _radius = 0.0f;
	};
}

#endif _MODEL_H
