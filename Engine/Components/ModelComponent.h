#ifndef _COMPONENT_MODEL_H
#define _COMPONENT_MODEL_H

#include "Framework/Component.h"
#include "RenderComponent.h"

namespace en
{
	class Renderer;
	class Model;
	class Material;

	class ModelComponent : public RenderComponent
	{
	public:
		ModelComponent() = default;

		CLONE(ModelComponent);

		virtual void Update() override {}
		virtual void Draw(Renderer& renderer) override;

		bool Write(const rapidjson::Value& value) const override;
		bool Read(const rapidjson::Value& value) override;

	public:
		std::shared_ptr<en::Model> model;
		std::shared_ptr<en::Material> material;

		bool depth_mask = true;

	};
}

#endif // _COMPONENT_MODEL_H