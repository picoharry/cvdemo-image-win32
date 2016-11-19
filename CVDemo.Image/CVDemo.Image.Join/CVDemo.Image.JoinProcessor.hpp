#pragma once

#include <string>
#include <vector>
#include <opencv2/core/core.hpp>


namespace cvdemo
{
	namespace image
	{
		class JoinProcessor
		{
		public:
			static int joinImageFiles(std::vector<std::string> imageFiles, std::string outputFolder = "");
			static cv::Mat joinImages(const cv::Mat& firstFrame, const cv::Mat& secondFrame);

		private:
			static cv::Mat joinImages(std::vector<std::string> imageFiles, const cv::Mat& lastFrame);
			static cv::Mat joinImages(const cv::Mat& firstFrame, std::vector<std::string> imageFiles);

		private:
			static std::string getOutputFilename();
		};
	}
}
