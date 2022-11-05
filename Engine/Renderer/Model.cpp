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
		/******** DEPRECATED ********************
		if (_points.size() == 1)
		{
			renderer.drawPoint(position, _color);
			return;
		}

		for (size_t i = 0; i < _points.size() - 1; i++)
		{
			renderer.drawLine(Vector2::rotate(_points[i] * scale, angle) + position, Vector2::rotate(_points[i + 1] * scale, angle) + position, _color);
		}
		**************************************/
	}

	void Model::Draw(Renderer& renderer, const Transform& transform)
	{	
		/******************* DEPRECATED	*********************************************
		if (_points.empty()) return;

		//Matrix3x3 mx = transform.matrix;

		if (_points.size() == 1)
		{
			//renderer.drawPoint(transform.position, _color);
			return;
		}

		for (size_t i = 0; i < _points.size() - 1; i++)
		{
			
			renderer.drawLine(
				Vector2::rotate(_points[i] * transform.scale, radians(transform.rotation)) + transform.position,
				Vector2::rotate(_points[i + 1] * transform.scale, radians(transform.rotation)) + transform.position,
				_color
			);
			
		} ****************************************************************************/
	}

	bool Model::Create(std::string filename, ...)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG("error loading assimp file %s", importer.GetErrorString());
			return false;
		}

		ProcessNode(scene->mRootNode, scene);

		return true;
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

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			ProcessMesh(mesh, scene);
		}
		// process the current node children 
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	void Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<vertex> vertices;

		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			vertex vertex;

			vertex.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
			vertex.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
			vertex.tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };
			if (mesh->mTextureCoords[0])
			{
				vertex.uv = { mesh->mTextureCoords[0][i].x, mesh -> mTextureCoords[0][i].y };
			}
			else
			{
				vertex.uv = { 0, 0 };
			}

			vertices.push_back(vertex);
		}

		_vertexBuffer.CreateVertexBuffer((GLsizei) (sizeof (vertex) * vertices.size()), (GLsizei) vertices.size(), vertices.data());
		_vertexBuffer.SetAttribute(0, 3, sizeof(vertex), 0);
		_vertexBuffer.SetAttribute(1, 2, sizeof(vertex), offsetof(vertex, uv));
		_vertexBuffer.SetAttribute(2, 3, sizeof(vertex), offsetof(vertex, normal));
		_vertexBuffer.SetAttribute(3, 3, sizeof(vertex), offsetof(vertex, tangent));

		std::vector<GLuint> indices;
		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		_vertexBuffer.CreateIndexBuffer(GL_UNSIGNED_INT, (GLsizei) indices.size(), indices.data());
	}
}