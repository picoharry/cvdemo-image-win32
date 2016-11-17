#pragma once

#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

namespace cvdemo
{
	namespace image
	{
		class StringHelper
		{
		private:
			StringHelper() {}

		public:
			static std::string trimLeft(const std::string& str)
			{
				std::string s(str);
				s.erase(s.begin(), std::find_if(s.begin(), s.end(),
					std::not1(std::ptr_fun<int, int>(std::isspace))));
				return s;
			}
			static std::string trimRight(const std::string& str)
			{
				std::string s(str);
				s.erase(std::find_if(s.rbegin(), s.rend(),
					std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
				return s;
			}
			static std::string trim(const std::string& str)
			{
				// return trimLeft(trimRight(str));
				std::string s(str);
				s.erase(s.begin(), std::find_if(s.begin(), s.end(),
					std::not1(std::ptr_fun<int, int>(std::isspace))));
				s.erase(std::find_if(s.rbegin(), s.rend(),
					std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
				return s;
			}

		public:
			static std::pair<std::string, std::string> split(const std::string& str, const char delim)
			{
				std::string first;
				std::string second;

				auto idx = str.find(delim);
				if (idx == -1) {
					first = str;
				}
				else {
					if (idx == 0) {
						// ???
						// When key=="", the value is ignored any way....
						second = str.substr(1);
					}
					else {
						first = str.substr(0, idx);
						second = str.substr(idx + 1);
					}
				}

				return std::make_pair(first, second);
			}

		};
	}
}
