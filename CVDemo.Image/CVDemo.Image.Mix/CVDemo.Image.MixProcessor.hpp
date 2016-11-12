#pragma once

#include <string>
#include <vector>
#include <opencv2/core/core.hpp>


namespace cvdemo
{
	namespace image
	{
		class MixProcessor
		{
		public:
			static int mixImages(const std::string fgImageFile, const std::string bgImageFile, const std::string outputFolder);
			static int mixImages(const std::vector<std::string> fgImageFiles, const std::string bgImageFile, const std::string outputFolder);
			static int mixImages(const std::string fgImageFile, const std::vector<std::string> bgImageFiles, const std::string outputFolder);
			// static int mixImages(const std::vector<std::string> fgImageFiles, const std::vector<std::string> bgImageFiles, const std::string outputFolder);

		public:
			static cv::Mat mixImage(const cv::Mat fgFrame, const cv::Mat bgFrame);

		private:
			static std::string getOutputFilename(const std::string fgImageFile, const std::string bgImageFile);
		};
	}
}
