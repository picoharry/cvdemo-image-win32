#pragma once

#include <string>
#include <vector>
#include <opencv2/core/core.hpp>


namespace cvdemo
{
	namespace image
	{
		class DiffProcessor
		{
		public:
			static int processImages(const std::vector<std::string> fgImageFiles, const std::vector<std::string> bgImageFiles);
			static int processImage(const std::string filename, const cv::Mat bgFrame);
		};
	}
}
