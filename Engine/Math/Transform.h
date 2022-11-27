#ifndef _TRANSFORM_H
#define _TRANSFORM_H
#include "MathUtils.h"

#include "Serialization/Serializable.h"

namespace en
{
	struct Transform : public Serializable
	{
		glm::vec3 position{ 0.0f };
		glm::vec3 scale{ 1.0f };
		glm::quat rotation;

		glm::mat4 matrix { 1.0f };

		Transform() = default;
		Transform(const glm::vec3& pos, const glm::quat& rot, const glm::vec3& scale = { 1.0f, 1.0f, 1.0f}) :
			position{pos}, rotation{rot}, scale{scale}
		{}

		virtual bool Write(const rapidjson::Value& value) const override
		{
			// TODO

			return true;
		}
		virtual bool Read(const rapidjson::Value& value) override
		{
			READ_DATA(value, position);
			READ_DATA(value, scale);

			glm::vec3 euler;
			READ_NAME_DATA(value, "rotation", euler);
			rotation = en::EulerToQuaternion(euler);

			return true;
		}

		glm::vec3 right() { return ((glm::mat4)(*this))[0]; }
		glm::vec3 up() { return ((glm::mat4)(*this))[1]; }
		glm::vec3 forward() { return ((glm::mat4)(*this))[2]; }

		/******************* Legacy ******************
		operator Matrix2x2 () const
		{
			Matrix2x2 mxS = Matrix2x2::scale(scale);
			Matrix2x2 mxR = Matrix2x2::rotate(en::radians(rotation));

			return { mxS * mxR };
		}
		*********************************************/

		void update()
		{
			matrix = *this;
		}

		void update(const glm::mat4& parent)
		{
			matrix = parent * (glm::mat4) (*this);
		}

		operator glm::mat4 () const
		{
			glm::mat4 mxS = glm::scale(scale);
			glm::mat4 mxR = glm::mat4_cast(rotation);
			glm::mat4 mxT = glm::translate(position);

			return { mxT * mxR * mxS };
		}
	};
}

#endif // _TRANSFORM_H