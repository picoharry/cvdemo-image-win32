// CVDemo.Image.Blend.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/video.hpp>
#include <stdio.h>
#include <sstream>
#include <stdexcept>
// #include <boost/program_options.hpp>
#include "CVDemo.Image.ProgramOptions.hpp"

using namespace cv;
using namespace std;
using namespace cvdemo::image;
// namespace po = boost::program_options;



int main(int argc, const char* argv[])
{
	// testing...
	string configFile = "../cvdemo.image.blend.cfg";
	ProgramOptions options = ProgramOptions(argc, argv, configFile);

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

		options.DisplayResizeAllowed(cerr);
		options.DisplayOutputImageMode(cerr);
		options.DisplayImageFileNames(cerr);
		options.DisplayBlendingWeights(cerr);
		// options.DisplayImageFileInfos(cerr);
		options.DisplayUnrecognizedArgs(cerr);

		options.DisplayUsageInfo(cerr);

		system("pause");
		return -1;
	}


	
	
	
	
	
	return 0;
}

