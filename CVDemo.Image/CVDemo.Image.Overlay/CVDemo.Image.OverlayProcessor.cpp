#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <opencv2/imgcodecs.hpp>
#include "CVDemo.Image.OverlayProcessor.hpp"

using namespace cv;
using namespace std;


namespace cvdemo
{
	namespace image
	{
		string OverlayProcessor::getOutputFilename(const string fgFilePath, const string bgFilePath)
		{
			//auto fgFN = string(find_if(fgFilePath.rbegin(), fgFilePath.rend(), "\\").base(), fgFilePath.end());
			//auto fgPivot = std::find(fgFN.rbegin(), fgFN.rend(), '.');
			//auto fgBase = (fgPivot == fgFN.rend()) ? fgFN : string(fgFN.begin(), fgPivot.base() - 1);
			auto fgFN = fgFilePath.substr(fgFilePath.find_last_of("/\\") + 1);
			auto fgDot = fgFN.find_last_of('.');
			auto fgBase = fgFN.substr(0, fgDot);

			//auto bgFN = string(find_if(bgFilePath.rbegin(), bgFilePath.rend(), "\\").base(), bgFilePath.end());
			//auto bgPivot = std::find(bgFN.rbegin(), bgFN.rend(), '.');
			//auto bgBase = (bgPivot == bgFN.rend()) ? bgFN : string(bgFN.begin(), bgPivot.base() - 1);
			//// auto bgExtension = (bgPivot == bgFN.rend()) ? "" : string(bgPivot.base() + 1, bgFN.end());  // ???
			//auto bgExtension = "png";   // tbd:
			auto bgFN = bgFilePath.substr(bgFilePath.find_last_of("/\\") + 1);
			auto bgDot = bgFN.find_last_of('.');
			auto bgBase = bgFN.substr(0, bgDot);
			auto bgExtension = bgFN.substr(bgDot + 1);

			string outputFN = fgBase + "-" + bgBase + "." + bgExtension;
			return outputFN;
		}

		int OverlayProcessor::overlayImages(const std::string fgImageFile, const std::string bgImageFile, const std::string outputFolder)
		{
			Mat fgFrame = imread(fgImageFile);
			if (fgFrame.empty()) {
				cerr << "Failed to open the fg image file: " + fgImageFile << endl;
				system("pause");
				return -1;
			}
			Mat bgFrame = imread(bgImageFile);
			if (bgFrame.empty()) {
				cerr << "Failed to open the bg image file: " + bgImageFile << endl;
				system("pause");
				return -1;
			}

			Mat overlaidFrame = overlayImage(fgFrame, bgFrame);
			string outputFilePath = outputFolder + "\\" + getOutputFilename(fgImageFile, bgImageFile);
			imwrite(outputFilePath, overlaidFrame);

			return 0;
		}
		int OverlayProcessor::overlayImages(const std::vector<std::string> fgImageFiles, const std::string bgImageFile, const std::string outputFolder)
		{
			for (auto f : fgImageFiles) {
				overlayImages(f, bgImageFile, outputFolder);
			}
			return 0;
		}
		int OverlayProcessor::overlayImages(const std::string fgImageFile, const std::vector<std::string> bgImageFiles, const std::string outputFolder)
		{
			for (auto b : bgImageFiles) {
				overlayImages(fgImageFile, b, outputFolder);
			}
			return 0;
		}

		Mat OverlayProcessor::overlayImage(const Mat fgFrame, const Mat bgFrame)
		{
			//Mat overlaidFrame;
			//auto alpha = 0.5;
			//auto beta = 0.5;
			//auto gamma = 0.5;
			//addWeighted(fgFrame, alpha, bgFrame, beta, gamma, overlaidFrame);

			Mat overlaidFrame;
			bgFrame.copyTo(overlaidFrame);

			for (auto y = 0; y < overlaidFrame.rows; y++) {
				for (auto x = 0; x < overlaidFrame.cols; x++) {
					auto opacity = ((double)fgFrame.data[y * fgFrame.step + x * fgFrame.channels() + 3]) / 255;
					if (opacity > 0.0) {
						for (int c = 0; c < overlaidFrame.channels(); ++c)
						{
							auto overlayPx = fgFrame.data[y * fgFrame.step + y * fgFrame.channels() + c];
							auto srcPx = overlaidFrame.data[y * fgFrame.step + x * fgFrame.channels() + c];
							overlaidFrame.data[y * overlaidFrame.step + overlaidFrame.channels() * x + c] = srcPx * (1. - opacity) + overlayPx * opacity;
						}
					}
				}
			}

			// For debugging.
			namedWindow("Foreground Frame");
			namedWindow("Background Frame");
			namedWindow("Overlaid Frame");

			imshow("Foreground Frame", fgFrame);
			imshow("Background Frame", bgFrame);
			imshow("Overlaid frame", overlaidFrame);

			return overlaidFrame;
		}
	}
}
