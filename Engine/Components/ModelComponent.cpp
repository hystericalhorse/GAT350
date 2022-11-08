#include "ModelComponent.h"

#include "Renderer/Material.h"
#include "Renderer/Model.h"
#include "Framework/Actor.h"
#include "Engine.h"

namespace en
{
	void ModelComponent::Draw(Renderer& renderer)
	{
		material->Bind();
		material->getProgram()->setUniform("model", (glm::mat4) _owner->_transform);
		material->getProgram()->setUniform("view", renderer.getView());
		material->getProgram()->setUniform("projection", renderer.getProjection());

		model->_vertexBuffer.Draw();
	}

	bool ModelComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool ModelComponent::Read(const rapidjson::Value& value)
	{
		std::string model;
		READ_DATA(value, model);
		this->model = __registry.Get<en::Model>(model);

		std::string material;
		READ_DATA(value, material);
		this->material = __registry.Get<en::Material>(material);

		return true;
	}
}