#pragma once

#include <string>
#include <vector>
#include <opencv2/core/core.hpp>


namespace cvdemo
{
	namespace image
	{
		// Random image generator.
		class RandomProcessor
		{
		public:
			//static cv::Mat generateRandomImage(
			//	int width, int height, 
			//	float weigthDots = 0.0f,
			//	float weigthLines = 0.0f,
			//	float weigthRectangles = 0.0f,
			//	float weigthCircles = 0.0f
			//);

		private:
			// tbd:
			static std::string getOutputFilename(const std::string fgImageFile, const std::string bgImageFile);
		};
	}
}
