#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <opencv2/imgcodecs.hpp>
#include "CVDemo.Image.ProgramOptions.hpp"
#include "CVDemo.Image.ProgramOptionsHelper.hpp"
#include "CVDemo.Image.MixProcessor.hpp"

using namespace cv;
using namespace std;


namespace cvdemo
{
	namespace image
	{
		string MixProcessor::getOutputFilename(const string fgFilePath, const string bgFilePath)
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

			string outputFN = fgBase + "-on-" + bgBase + "." + bgExtension;
			cout << "Output image file name: " << outputFN << endl;

			return outputFN;
		}

		int MixProcessor::mixImages(const std::string fgImageFile, const std::string bgImageFile, const std::string outputFolder)
		{
			// Mat fgFrame = imread(fgImageFile, IMREAD_UNCHANGED);
			Mat fgFrame = imread(fgImageFile, -1);
			if (fgFrame.empty()) {
				cerr << "Failed to open the fg image file: " + fgImageFile << endl;
				system("pause");
				return -1;
			}
			// Mat bgFrame = imread(bgImageFile, IMREAD_UNCHANGED);
			Mat bgFrame = imread(bgImageFile, -1);
			if (bgFrame.empty()) {
				cerr << "Failed to open the bg image file: " + bgImageFile << endl;
				system("pause");
				return -1;
			}

			Mat overlaidFrame = mixImage(fgFrame, bgFrame);

			string outputFilePath = outputFolder + "/" + getOutputFilename(fgImageFile, bgImageFile);
			cout << "Output image file path: " << outputFilePath << endl;

			imwrite(outputFilePath, overlaidFrame);

			return 0;
		}
		int MixProcessor::mixImages(const std::vector<std::string> fgImageFiles, const std::string bgImageFile, const std::string outputFolder)
		{
			for (auto f : fgImageFiles) {
				mixImages(f, bgImageFile, outputFolder);
			}
			return 0;
		}
		int MixProcessor::mixImages(const std::string fgImageFile, const std::vector<std::string> bgImageFiles, const std::string outputFolder)
		{
			for (auto b : bgImageFiles) {
				mixImages(fgImageFile, b, outputFolder);
			}
			return 0;
		}

		// Note:
		// For our use case,
		// fgFrame and bgFrame are exactly the same size (tbd: it can be generalized...)
		// Both fgFrame and bgFrame should have alpha channels (meaning we only support PNG files at this point?).
		Mat MixProcessor::mixImage(const Mat fgFrame, const Mat bgFrame)
		{
			ProgramOptions options = ProgramOptionsHelper::getInstance().getProgramOptions();
			auto alpha = options.GetBlendingWeightAlpha();
			auto beta = options.GetBlendingWeightBeta();
			auto gamma = options.GetBlendingWeightGamma();

			Mat overlaidFrame;
			addWeighted(fgFrame, alpha, bgFrame, beta, gamma, overlaidFrame);


			// For debugging.
			// imshow("Foreground Frame", fgFrame);
			// waitKey(10);
			// imshow("Background Frame", bgFrame);
			// waitKey(10);
			imshow("Overlaid Frame", overlaidFrame);
			waitKey(10);

			return overlaidFrame;
		}
	}
}
