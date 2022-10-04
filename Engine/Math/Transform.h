#ifndef _TRANSFORM_H
#define _TRANSFORM_H
#include "Vector2.h"
#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "MathUtils.h"

#include "Serialization/Serializable.h"

namespace en
{
	struct Transform : public Serializable
	{
		Transform() = default;
		Transform(const Vector2& pos, float rot, Vector2 sca) :
			position{pos}, rotation{rot}, scale{sca}
		{}

		Vector2 position { 0,0 };
		Vector2 scale { 1, 1 };
		float rotation = 0.0f; // rotation in degrees
		Matrix3x3 matrix;

		virtual bool Write(const rapidjson::Value& value) const override
		{
			// TODO

			return true;
		}
		virtual bool Read(const rapidjson::Value& value) override
		{
			READ_DATA(value, position);
			READ_DATA(value, scale);
			READ_DATA(value, rotation);

			return true;
		}

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
			Matrix3x3 mxS = Matrix3x3::scale(scale);
			Matrix3x3 mxR = Matrix3x3::rotate(en::radians(rotation));
			Matrix3x3 mxT = Matrix3x3::translate(position);

			matrix = { mxT * mxR * mxS };
		}

		void update(const Matrix3x3& parent)
		{
			Matrix3x3 mxS = Matrix3x3::scale(scale);
			Matrix3x3 mxR = Matrix3x3::rotate(en::radians(rotation));
			Matrix3x3 mxT = Matrix3x3::translate(position);

			matrix = { mxT * mxR * mxS };
			matrix = parent * matrix;
		}

		operator Matrix3x3 () const
		{
			Matrix3x3 mxS = Matrix3x3::scale(scale);
			Matrix3x3 mxR = Matrix3x3::rotate(en::radians(rotation));
			Matrix3x3 mxT = Matrix3x3::translate(position);

			return { mxT * mxR * mxS };
		}
	};
}

#endif // _TRANSFORM_H