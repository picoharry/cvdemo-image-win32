#pragma once

#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>


namespace cvdemo
{
	namespace image
	{
		class SubtractProcessor
		{
		public:
			static int processImages(const std::vector<std::string> imageFiles);
			static int processImage(const std::string filename, cv::Ptr<cv::BackgroundSubtractor> pMOG2);
		};
	}
}
