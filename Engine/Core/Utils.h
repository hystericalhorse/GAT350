#ifndef _UTILS_H
#define _UTILS_H

#include <cctype>
#include <algorithm>

namespace en
{
	class Utils
	{
	public:
		static std::string make_lowercase(const std::string& s)
		{
			std::string lwr = s;

			std::transform(lwr.begin(), lwr.end(), lwr.begin(), [](unsigned char c) { return std::tolower(c); });

			return lwr;
		}

		static std::string make_uppercase(const std::string& s)
		{
			std::string upr = s;

			std::transform(upr.begin(), upr.end(), upr.begin(), [](unsigned char c) { return std::toupper(c); });

			return upr;
		}

		/// <summary>
		/// Returns false if the strings do not match. Is case-senstive.
		/// </summary>
		/// <param name="s1">First string to be compared</param>
		/// <param name="s2">Second string to be compared</param>
		/// <returns></returns>
		static bool sensitive_compare_strings(const std::string& s1, const std::string& s2)
		{
			if (s1.length() != s2.length()) return false;

			for (size_t i = 0; i < s1.length(); i++)
			{
				if (s1[i] != s2[i]) return false;
			}

			return true;
		}

		/// <summary>
		/// Returns false if the strings do not match. Is not case-sensitive.
		/// </summary>
		/// <param name="s1">First string to be compared</param>
		/// <param name="s2">Second string to be compared</param>
		/// <returns></returns>
		static bool compare_strings(const std::string& s1, const std::string& s2)
		{
			if (s1.length() != s2.length()) return false;
			std::string l1 = make_lowercase(s1);
			std::string l2 = make_lowercase(s2);

			for (size_t i = 0; i < s1.length(); i++)
			{
				if (l1[i] != l2[i]) return false;
			}

			return true;
		}
	};
}

#endif // _UTILS_H