#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <opencv2/core.hpp>


namespace cvdemo
{
	namespace image
	{
		class ImageSizeUtil
		{
		private:
			ImageSizeUtil() {}

		private:
			static const char CHAR_DIM_SEPARATOR = 'x';

		public:
			static cv::Size parse(const std::string& line);

		private:
			// <width, height> of kernel size.
			static std::pair<int, int> _parse(const std::string& line);

		};
	}
}
