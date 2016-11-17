// CVDemo.Image.Random.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <sstream>
#include <stdexcept>
#include <ctime>
// #include <boost/program_options.hpp>
// #include <boost/filesystem.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include "CVDemo.Image.ProgramOptions.hpp"
#include "CVDemo.Image.ProgramOptionsHelper.hpp"

using namespace cv;
using namespace std;
using namespace cvdemo::image;
// namespace po = boost::program_options;
// using namespace boost::filesystem;


static const string WINDOW_NAME = "Display window";
static RNG rng;

// Forward decl.
static Scalar randomColor();
void drawRandomLines(Mat& img, Rect bounds, int countLines);
void drawRandomCircles(Mat& img, Rect bounds, int countCircles);
void drawRandomRectangles(Mat& img, Rect bounds, int countRectangles);
void drawRandomDots(Mat& img, Rect bounds, int countDots);


int main(int argc, const char* argv[])
{
	// testing...
	string configFile = "../cvdemo.image.random.cfg";
	// ProgramOptions options = ProgramOptions(argc, argv, configFile);
	ProgramOptionsHelper::getInstance().initialize(argc, argv, configFile);
	ProgramOptions& options = ProgramOptionsHelper::getInstance().getProgramOptions();

	if (options.IsForUsageInfo()) {
		options.DisplayUsageInfo(cout);
		system("pause");
		return -1;
	}
	if (options.IsForVersionInfo()) {
		cout << "Version = 0.0.1" << endl;
		system("pause");
		return -1;
	}
	if (options.IsForOptionsDisplay()) {
		options.DisplayInputOptions(cout);
		system("pause");
		return -1;
	}

	if (!options.IsValid()) {
		cerr << ">>> Invalid input options." << endl;

		options.DisplayUnrecognizedArgs(cerr);
		options.DisplayOutputImageType(cerr);
		options.DisplayOutputImageFolder(cerr);
		options.DisplayElementWeightForDots(cerr);
		options.DisplayElementWeightForLines(cerr);
		options.DisplayElementWeightForRectangles(cerr);
		options.DisplayElementWeightForCircles(cerr);

		options.DisplayUsageInfo(cerr);

		system("pause");
		return EXIT_FAILURE;
	}


	// Initialize RNG.
	// TBD: Does this work???
	rng(time(nullptr) * 0xFFFFFF);


	auto imageSize = options.GetImageSize();
	//Point p1(-imageSize.width / 2, -imageSize.height / 2);
	//Point p2((imageSize.width * 3) / 2, (imageSize.height * 3) / 2);
	Rect bounds(-imageSize.width / 2, -imageSize.height / 2, imageSize.width * 2, imageSize.height * 2);


	auto totalCount = options.GetRandomElementCount();
	auto weightLines = options.GetElementWeightForLines();
	auto weightCircles = options.GetElementWeightForCircles();
	auto weightRectangles = options.GetElementWeightForRectangles();
	auto weightDots = options.GetElementWeightForDots();
	auto totalWeights = weightDots + weightLines + weightRectangles + weightCircles;
	auto countLines = (int)((totalCount * weightLines) / totalWeights);
	auto countCircles = (int)((totalCount * weightCircles) / totalWeights);
	auto countRectangles = (int)((totalCount * weightRectangles) / totalWeights);
	auto countDots = (int)((totalCount * weightDots) / totalWeights);


	//auto b = rng.uniform(0, 255);
	//auto g = rng.uniform(0, 255);
	//auto r = rng.uniform(0, 255);
	auto bgColor = randomColor();
	// Mat img = Mat::zeros(imageSize.width, imageSize.height, CV_8UC3);
	// Mat img(imageSize.width, imageSize.height, CV_8UC3, Scalar(255, 255, 255));
	// Mat img(imageSize.width, imageSize.height, CV_8UC3, Scalar(200, 0, 0));
	// Mat img(imageSize.width, imageSize.height, CV_8UC3, Scalar(b, g, r));
	Mat img(imageSize.width, imageSize.height, CV_8UC3, Scalar(bgColor[0], bgColor[1], bgColor[2]));

	//imshow(WINDOW_NAME, img);
	//waitKey(0);


	// TBD:
	// Pick element types randomly 
	// rather than going through them one by one.

	drawRandomLines(img, bounds, countLines);
	//imshow(WINDOW_NAME, img);
	//waitKey(0);

	drawRandomCircles(img, bounds, countCircles);
	//imshow(WINDOW_NAME, img);
	//waitKey(0);

	drawRandomRectangles(img, bounds, countRectangles);
	//imshow(WINDOW_NAME, img);
	//waitKey(0);

	drawRandomDots(img, bounds, countDots);
	//imshow(WINDOW_NAME, img);
	//waitKey(0);




	imshow(WINDOW_NAME, img);
	waitKey(0);
	// system("pause");
	return EXIT_SUCCESS;
}


static Scalar randomColor()
{
	int icolor = (unsigned)rng;
	return Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

void drawRandomLines(Mat& img, Rect bounds, int countLines)
{
	Point pt1, pt2;
	for (auto l = 0; l < countLines; l++) {
		pt1.x = rng.uniform(bounds.x, bounds.x + bounds.width);
		pt1.y = rng.uniform(bounds.y, bounds.y + bounds.height);
		pt2.x = rng.uniform(bounds.x, bounds.x + bounds.width);
		pt2.y = rng.uniform(bounds.y, bounds.y + bounds.height);

		line(img, pt1, pt2, randomColor(), rng.uniform(1, 10), 8);
	}
}

void drawRandomCircles(Mat& img, Rect bounds, int countCircles)
{
	int lineType = 8;
	Point center;
	for (auto c = 0; c < countCircles; c++) {
		center.x = rng.uniform(bounds.x, bounds.x + bounds.width);
		center.y = rng.uniform(bounds.y, bounds.y + bounds.height);

		circle(img, center, rng.uniform(0, 300), randomColor(), rng.uniform(-1, 9), lineType);
	}
}

void drawRandomRectangles(Mat& img, Rect bounds, int countRectangles)
{
	Point pt1, pt2;
	int lineType = 8;
	int thickness = rng.uniform(-3, 10);
	for (auto r = 0; r < countRectangles; r++) {
		pt1.x = rng.uniform(bounds.x, bounds.x + bounds.width);
		pt1.y = rng.uniform(bounds.y, bounds.y + bounds.height);
		pt2.x = rng.uniform(bounds.x, bounds.x + bounds.width);
		pt2.y = rng.uniform(bounds.y, bounds.y + bounds.height);

		rectangle(img, pt1, pt2, randomColor(), MAX(thickness, -1), lineType);
	}
}

void drawRandomDots(Mat& img, Rect bounds, int countDots)
{
	int lineType = 8;
	Point center;
	Size axes;
	for (auto d = 0; d < countDots; d++) {
		center.x = rng.uniform(bounds.x, bounds.x + bounds.width);
		center.y = rng.uniform(bounds.y, bounds.y + bounds.height);

		axes.width = rng.uniform(0, 30);
		axes.height = rng.uniform(0, 30);
		double angle = rng.uniform(0, 180);

		ellipse(img, center, axes, angle, angle - 100, angle + 200, randomColor(), rng.uniform(-1, 9), lineType);
	}
}
