#ifndef _MATRIX_2X2_H
#define _MATRIX_2X2_H

#include "Vector2.h"

namespace en
{
	struct Matrix2x2
	{
		Vector2 rows[2];

		Matrix2x2() = default;
		Matrix2x2(const Vector2& v1, const Vector2& v2);

		Vector2 operator [] (size_t index) const { return rows[index]; }
		Vector2& operator [] (size_t index) { return rows[index]; }

		Vector2 operator * (const Vector2& v)
		{
			return Vector2 { 
				(v.x * rows[0][0]) + (v.y * rows[0][1]),
				(v.x * rows[1][0]) + (v.y * rows[1][1])
			};
		}

		Matrix2x2 operator * (const Matrix2x2& m)
		{
			Matrix2x2 r;

			r[0][0] = (m[0][0] * rows[0][0]) + (m[0][1] * rows[1][0]);
			r[0][1] = (m[0][0] * rows[0][1]) + (m[0][1] * rows[1][1]);
			r[1][0] = (m[1][0] * rows[0][0]) + (m[1][1] * rows[1][0]);
			r[1][1] = (m[1][0] * rows[0][1]) + (m[1][1] * rows[1][1]);

			return r;
		}

		static Matrix2x2 scale(const Vector2& scale);
		static Matrix2x2 scale(float scale); // strictly uniform

		static Matrix2x2 rotate(float radians);

		static const Matrix2x2 identity;
		static const Matrix2x2 zero;

	};

	inline Matrix2x2::Matrix2x2(const Vector2& v1, const Vector2& v2)
	{
		rows[0] = v1; rows[1] = v2;
	}

	inline Matrix2x2 Matrix2x2::scale(const Vector2& scale) // Scale
	{
		Matrix2x2 mx;

		// {sX, 0}, {0, sY}

		mx[0] = Vector2 { scale.x, 0.0f };
		mx[1] = Vector2 { 0.0f, scale.y };
		
		return mx;
	}

	inline Matrix2x2 Matrix2x2::scale(float scale) // Strict Uniform Scale
	{
		Matrix2x2 mx;

		// {sX, 0}, {0, sY}

		mx[0] = Vector2{ scale, 0.0f };
		mx[1] = Vector2{ 0.0f, scale };

		return mx;
	}

	inline Matrix2x2 Matrix2x2::rotate(float radians)
	{
		Matrix2x2 mx;

		float s = std::sin(radians);
		float c = std::cos(radians);

		// {cos r, -sin r}, {sin r, cos r}

		mx[0] = Vector2 { c, -s };
		mx[1] = Vector2 { s, c };

		return mx;
	}
}

#endif // _MATRIX_2X2_H