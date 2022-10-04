#include "ModelComponent.h"

#include "Engine.h"
#include "Renderer/Model.h"
#include "Framework/Actor.h"

namespace en
{
	void ModelComponent::Update()
	{

	}

	void ModelComponent::Draw(Renderer& renderer)
	{
		_model->Draw(renderer, _owner->_Transform());
	}

	bool ModelComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool ModelComponent::Read(const rapidjson::Value& value)
	{
		std::string model;
		READ_DATA(value, model);

		_model = en::__registry.Get<en::Model>(model);

		return true;
	}
}