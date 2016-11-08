#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <opencv2/imgcodecs.hpp>
#include "CVDemo.Image.DiffProcessor.hpp"

using namespace cv;
using namespace std;


namespace cvdemo
{
	namespace image
	{
		int DiffProcessor::processImages(const std::vector<std::string> fgImageFiles, const std::vector<std::string> bgImageFiles)
		{
			// create GUI windows
			namedWindow("Frame");
			namedWindow("Foreground - background");

			// Background image:
			// TBD: Blend or take "average" of all background images...
			// For now, we just use the first element.
			Mat bgFrame = imread(bgImageFiles[0]);
			if (bgFrame.empty()) {
				//error in opening the image
				system("pause");
				return -1;
			}


			for (auto f : fgImageFiles) {
				if (processImage(f, bgFrame)) {
					cerr << "Failed to process the image file: " << f << endl;
					exit(EXIT_FAILURE);
				}
				char keyboard = (char)0;
				while (keyboard != 'q' && keyboard != 27) {
					keyboard = waitKey(10);
				}
			}
			cout << "Processed all image files." << endl;

			// destroy GUI windows
			destroyAllWindows();

			return 0;
		}
		int DiffProcessor::processImage(const std::string filename, const cv::Mat bgFrame)
		{
			static int counter = 0;

			// Read the foreground file.
			Mat fgFrame = imread(filename);
			if (fgFrame.empty()) {
				return -1;
			}

			// Just use diff...
			Mat bgSubtracted;
			absdiff(fgFrame, bgFrame, bgSubtracted);

			rectangle(fgFrame, cv::Point(10, 2), cv::Point(100, 20),
				cv::Scalar(255, 255, 255), -1);
			putText(fgFrame, std::to_string(counter), cv::Point(15, 15),
				FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));

			//show the current frame and the fg masks
			imshow("Frame", fgFrame);
			imshow("Foreground - background", bgSubtracted);

			//int keyboard = 0;
			//while ((char)keyboard != 'q' && (char)keyboard != 27) {
			//	//get the input from the keyboard
			//	keyboard = waitKey(30);
			//}
			counter++;

			return 0;
		}
	}
}
