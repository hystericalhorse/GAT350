#ifndef _MATRIX_3X3_H
#define _MATRIX_3X3_H

#include "Vector2.h"
#include "Vector3.h"

namespace en
{
	struct Matrix3x3
	{
		Vector3 rows[3];

		Matrix3x3() = default;
		Matrix3x3(const Vector3& v1, const Vector3& v2, const Vector3& v3);

		Vector3 operator [] (size_t index) const { return rows[index]; }
		Vector3& operator [] (size_t index) { return rows[index]; }

		Vector3 operator * (const Vector3& v) const
		{
			return Vector3
			{
				(v.x * rows[0][0]) + (v.y * rows[0][1]) + (1.0f * rows[0][2]),
				(v.x * rows[1][0]) + (v.y * rows[1][1]) + (1.0f * rows[1][2]),
				1.0f
			};
		}

		Vector2 operator * (const Vector2& v) const
		{
			return Vector2
			{
				v.x * rows[0][0] + v.y * rows[0][1] + 1.0f * rows[0][2], // leave in 1.0f as a reminder of formula
				v.x * rows[1][0] + v.y * rows[1][1] + 1.0f * rows[1][2]  // leave in 1.0f as a reminder of formula
			};
		}

		Matrix3x3 operator * (const Matrix3x3& m) const
		{
			Matrix3x3 r;

			r[0][0] = m[0][0] * rows[0][0] + m[1][0] * rows[0][1] + m[2][0] * rows[0][2];
			r[0][1] = m[0][1] * rows[0][0] + m[1][1] * rows[0][1] + m[2][1] * rows[0][2];
			r[0][2] = m[0][2] * rows[0][0] + m[1][2] * rows[0][1] + m[2][2] * rows[0][2];

			r[1][0] = m[0][0] * rows[1][0] + m[1][0] * rows[1][1] + m[2][0] * rows[1][2];
			r[1][1] = m[0][1] * rows[1][0] + m[1][1] * rows[1][1] + m[2][1] * rows[1][2];
			r[1][2] = m[0][2] * rows[1][0] + m[1][2] * rows[1][1] + m[2][2] * rows[1][2];

			r[2][0] = (m[0][0] * rows[2][0]) + (m[1][0] * rows[2][1]) + (m[2][0] * rows[2][2]);
			r[2][1] = (m[0][1] * rows[2][0]) + (m[1][1] * rows[2][1]) + (m[2][1] * rows[2][2]);
			r[2][2] = (m[0][2] * rows[2][0]) + (m[1][2] * rows[2][1]) + (m[2][2] * rows[2][2]);

			return r;
		}

		static Matrix3x3 scale(const Vector2& scale);
		static Matrix3x3 scale(float scale); // strictly uniform

		Vector2 get_translation() const
		{
			return { rows[0][2], rows[1][2] };
		}

		float get_rotation() const
		{
			return std::atan2(rows[1][0], rows[0][0]);
		}

		Vector2 get_scale() const
		{
			Vector2 x = { rows[0][0], rows[0][1] };
			Vector2 y = { rows[1][0], rows[1][1] };

			return { x.length(), y.length() };
		}

		static Matrix3x3 rotate(float radians);

		static Matrix3x3 translate(const Vector2& distance);

		static const Matrix3x3 identity;
		static const Matrix3x3 zero;
	};

	inline Matrix3x3::Matrix3x3(const Vector3& v1, const Vector3& v2, const Vector3& v3)
	{
		rows[0] = v1; rows[1] = v2; rows[2] = v3;
	}

	inline Matrix3x3 Matrix3x3::scale(const Vector2& scale) // Scale
	{
		Matrix3x3 mx = identity;

		// {sX, 0, 0}, {0, sY, 0}, (0, 0, 1)

		mx[0][0] = scale.x;
		mx[1][1] = scale.y;

		return mx;
	}

	inline Matrix3x3 Matrix3x3::scale(float scale) // Strict Uniform Scale
	{
		Matrix3x3 mx = identity;

		// {sX, 0}, {0, sY}

		mx[0][0] = scale;
		mx[1][1] = scale;

		return mx;
	}

	inline Matrix3x3 Matrix3x3::rotate(float radians)
	{
		Matrix3x3 mx = identity;

		float s = std::sin(radians);
		float c = std::cos(radians);

		// {cos r, -sin r}, {sin r, cos r}

		mx[0] = Vector3{ c, -s, 0.0f };
		mx[1] = Vector3{ s, c, 0.0f };

		return mx;
	}

	inline Matrix3x3 Matrix3x3::translate(const Vector2& distance)
	{
		Matrix3x3 mx = identity;

		mx[0][2] = distance.x;
		mx[1][2] = distance.y;

		return mx;
	}
};

#endif // _MATRIX_3X3_H