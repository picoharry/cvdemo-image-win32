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
#include "CVDemo.Image.JoinProcessor.hpp"

using namespace cv;
using namespace std;


namespace cvdemo
{
	namespace image
	{
		string JoinProcessor::getOutputFilename()
		{
			// tbd:
			return "joined-output-image.png";
		}

		// TBD:
		// Just use cv::ArrayOfArrays for h|vconcat() ???
		int JoinProcessor::joinImageFiles(std::vector<std::string> imageFiles, std::string outputFolder)
		{
			// temporary. Processing order.
			auto firstFirst = false;

			Mat joined;
			Mat firstFrame;
			Mat lastFrame;
			auto size = imageFiles.size();
			switch (size) {
			case 0:
				// This should not happen.
				// throw runtime_error("Invalid arguments. imageFiles is empty.");
				return -1;
			case 1:
				// read the iamge;
				lastFrame = imread(imageFiles[0], -1);
				if (lastFrame.empty()) {
					cerr << "Failed to open the image file: " + imageFiles[0] << endl;
					// throw runtime_error("Failed to open the image file: " + imageFiles[0]);
					return -1;
				}
				joined = lastFrame;
				break;
			default:
				if (firstFirst) {
					std::reverse(imageFiles.begin(), imageFiles.end());
					firstFrame = imread(imageFiles[size - 1], -1);
					if (firstFrame.empty()) {
						cerr << "Failed to open the image file: " + imageFiles[size - 1] << endl;
						// throw runtime_error("Failed to open the image file: " + imageFiles[size - 1]);
						return -1;
					}
					imageFiles.pop_back();
					joined = joinImages(firstFrame, imageFiles);
				}
				else {
					lastFrame = imread(imageFiles[size - 1], -1);
					if (lastFrame.empty()) {
						cerr << "Failed to open the image file: " + imageFiles[size - 1] << endl;
						// throw runtime_error("Failed to open the image file: " + imageFiles[size - 1]);
						return -1;
					}
					imageFiles.pop_back();
					joined = joinImages(imageFiles, lastFrame);
				}
				break;
			}

			// For debugging...
			imshow("Joined Frame", joined);
			waitKey(3000);

			string outputFilePath = (outputFolder == "") ? getOutputFilename() : outputFolder + "/" + getOutputFilename();
			cout << "Output image file path: " << outputFilePath << endl;

			imwrite(outputFilePath, joined);
			return 0;
		}

		Mat JoinProcessor::joinImages(std::vector<std::string> imageFiles, const Mat& lastFrame)
		{
			Mat joined;
			Mat firstFrame;
			Mat trailingFrame;
			auto size = imageFiles.size();
			switch (size) {
			case 0:
				joined = lastFrame;
				return joined;
			case 1:
				// read the iamge;
				firstFrame = imread(imageFiles[0], -1);
				if (firstFrame.empty()) {
					cerr << "Failed to open the image file: " + imageFiles[0] << endl;
					throw runtime_error("Failed to open the image file: " + imageFiles[0]);
				}
				joined = joinImages(firstFrame, lastFrame);
				return joined;
			default:
				trailingFrame = imread(imageFiles[size - 1], -1);
				if (trailingFrame.empty()) {
					cerr << "Failed to open the image file: " + imageFiles[size - 1] << endl;
					throw runtime_error("Failed to open the image file: " + imageFiles[size - 1]);
				}
				imageFiles.pop_back();
				firstFrame = joinImages(imageFiles, trailingFrame);
				joined = joinImages(firstFrame, lastFrame);
				return joined;
			}
		}

		// We assume that the image Files are reversely inserted into the imageFiles vector.
		Mat JoinProcessor::joinImages(const Mat& firstFrame, std::vector<std::string> imageFiles)
		{
			Mat joined;
			Mat lastFrame;
			Mat leadingFrame;
			auto size = imageFiles.size();
			switch (size) {
			case 0:
				joined = firstFrame;
				return joined;
			case 1:
				// read the iamge;
				lastFrame = imread(imageFiles[0], -1);
				if (lastFrame.empty()) {
					cerr << "Failed to open the image file: " + imageFiles[0] << endl;
					throw runtime_error("Failed to open the image file: " + imageFiles[0]);
				}
				joined = joinImages(firstFrame, lastFrame);
				return joined;
			default:
				leadingFrame = imread(imageFiles[size - 1], -1);
				if (leadingFrame.empty()) {
					cerr << "Failed to open the image file: " + imageFiles[size - 1] << endl;
					throw runtime_error("Failed to open the image file: " + imageFiles[size - 1]);
				}
				imageFiles.pop_back();
				lastFrame = joinImages(leadingFrame, imageFiles);
				joined = joinImages(firstFrame, lastFrame);
				return joined;
			}
		}

		Mat JoinProcessor::joinImages(const Mat& lhsFrame, const Mat& rhsFrame)
		{
			Mat joined;
			ProgramOptions options = ProgramOptionsHelper::getInstance().getProgramOptions();
			auto orientation = options.GetImageJoinOrientation();
			if (orientation == "v" || orientation == "vertical") {
				cv::vconcat(lhsFrame, rhsFrame, joined);
			}
			else {  // "horizontal" is default.
				cv::hconcat(lhsFrame, rhsFrame, joined);
			}

			//// For debugging.
			//// imshow("First Frame", lhsFrame);
			//// waitKey(10);
			//// imshow("Second Frame", rhsFrame);
			//// waitKey(10);
			//imshow("Joined Frame", joined);
			//waitKey(3000);

			return joined;
		}
	}
}
