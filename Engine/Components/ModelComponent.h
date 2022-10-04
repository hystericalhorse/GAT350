#ifndef _COMPONENT_MODEL_H
#define _COMPONENT_MODEL_H

#include "RenderComponent.h"

namespace en
{
	class Model;

	class ModelComponent : public RenderComponent
	{
	public:
		ModelComponent() = default;
		~ModelComponent() = default;

		CLONE(ModelComponent)

		void Update() override;
		void Draw(Renderer& renderer) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		bool get()
		{
			if (_model == nullptr) return false;

			return true;
		}

	public:
		std::shared_ptr<Model> _model = std::make_shared<Model>();

	};
}

#endif // _COMPONENT_MODEL_H