#ifndef _MATH_UTILS_H
#define _MATH_UTILS_H

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/color_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/quaternion.hpp>

namespace en
{
	constexpr float pi = 3.14159265359f;
	constexpr float two_pi = 6.28318530718f;
	constexpr float half_pi = 1.57079632679f;

	constexpr float radians(float degrees)
	{
		return degrees * (pi / 180);
	}

	constexpr float degrees(float radians)
	{
		return radians * (180 / pi);
	}

	glm::vec3 QuaternionToEuler(glm::quat q);
	glm::quat EulerToQuaternion(glm::vec3 euler);

	float abs(float i);

	template <typename T>
	T clamp(T value, T min, T max)
	{
		if (value < min) return min;
		if (value > max) return max;

		return value;
	}

	template <typename T>
	T lerp(T min, T max, float t)
	{
		t = clamp(t, 0.0f, 1.0f);

		return min + ((max-min) * t);
	}

	template <typename T>
	T normalise(T value, T min, T max)
	{
		return (value - min) / (max - min);
	}

	template <typename T>
	T remap(T value, T minIn, T maxIn, T minOut, T maxOut)
	{
		return lerp(minOut, maxOut, normalise(value, minIn, maxIn));
	}

	template <typename T>
	T mod(T numerator, T denominator)
	{
		return std::fmod(numerator, denominator);
	}

	template <>
	inline int mod(int numerator, int denominator)
	{
		return numerator % denominator;
	}

	template <typename T>
	T wrap(T value, T min, T max)
	{
		if (value < min) return max - mod((min - value), (max - min));
		if (value > max) return min + mod((value - min), (max - min));

		return value;
	}
}

#endif // _MATH_UTILS_H