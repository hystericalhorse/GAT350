#ifndef _VECTOR3_H
#define _VECTOR3_H

#include <cmath>
#include <istream>
#include <string>

namespace en
{
	struct Vector3
	{
		float x, y, z;

		Vector3() = default;
		Vector3(float x, float y, float z) :
			x{ x }, y{ y }, z{ z }
		{}
		Vector3(float v) :
			x{ v }, y{ v }, z{ v }
		{}
		Vector3(int x, int y, int z)
		{
			this->x = (float) x;
			this->y = (float) y;
			this->z = (float) z;
		}
		Vector3(double x, double y, double z)
		{
			this->x = (float) x;
			this->y = (float) y;
			this->z = (float) z;
		}

		void set(float x, float y) { this->x = x; this->y = y; }
		float operator [] (size_t index) const { return (&x)[index]; }
		float& operator [] (size_t index) { return (&x)[index]; }

		Vector3 operator + (const Vector3& v) const { return Vector3(this->x + v.x, this->y + v.y, this->z + v.z); }
		Vector3 operator - (const Vector3& v) const { return Vector3(this->x - v.x, this->y - v.y, this->z - v.z); }
		Vector3 operator * (const Vector3& v) const { return Vector3(this->x * v.x, this->y * v.y, this->z * v.z); }
		Vector3 operator / (const Vector3& v) const { return Vector3(this->x / v.x, this->y / v.y, this->z / v.z); }

		Vector3 operator += (const Vector3& v) { this->x += v.x; this->y += v.y; this->z += v.z; return *this; }
		Vector3 operator -= (const Vector3& v) { this->x -= v.x; this->y -= v.y; this->z -= v.z; return *this; }
		Vector3 operator *= (const Vector3& v) { this->x *= v.x; this->y *= v.y; this->z *= v.z; return *this; }
		Vector3 operator /= (const Vector3& v) { this->x /= v.x; this->y /= v.y; this->z /= v.z; return *this; }

		Vector3 operator + (float s) const { return Vector3(this->x + s, this->y + s, this->z + s); }
		Vector3 operator - (float s) const { return Vector3(this->x - s, this->y - s, this->z - s); }
		Vector3 operator * (float s) const { return Vector3(this->x * s, this->y * s, this->z * s); }
		Vector3 operator / (float s) const { return Vector3(this->x / s, this->y / s, this->z / s); }

		Vector3 operator += (float s) { this->x += s; this->y += s; this->z += s; return *this; }
		Vector3 operator -= (float s) { this->x -= s; this->y -= s; this->z -= s; return *this; }
		Vector3 operator *= (float s) { this->x *= s; this->y *= s; this->z *= s; return *this; }
		Vector3 operator /= (float s) { this->x /= s; this->y /= s; this->z /= s; return *this; }

		Vector3 operator - () const { return Vector3{ -x, -y, -z }; }

		bool operator == (const Vector3& v) const { return (this->x == v.x && this->y == v.y && this->z == v.z); }
		bool operator != (const Vector3& v) const { return (this->x != v.x || this->y != v.y || this->z != v.z); }

		inline float length() { return std::sqrt((x * x) + (y * y) + (z * z)); }
		inline float length_sqr() { return (x * x) + (y * y) + (z * z); }

		inline float distance(const Vector3& v) { return (*this - v).length(); }
		inline float distance_sqr(const Vector3& v) { return (*this - v).length_sqr(); }

		inline Vector3 normalised()
		{
			float l = length();
			return Vector3(this->x / l, this->y / l, this->z / l);
		}

		inline void normalise()
		{
			(*this) /= length();
		}

	};
}

#endif // _VECTOR3_H