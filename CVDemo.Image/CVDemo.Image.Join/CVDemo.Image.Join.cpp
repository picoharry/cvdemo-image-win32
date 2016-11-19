// CVDemo.Image.Join.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <stdio.h>
#include <sstream>
#include <stdexcept>
// #include <boost/program_options.hpp>
// #include <boost/filesystem.hpp>
#include "CVDemo.Image.FileSystemHelper.hpp"
#include "CVDemo.Image.ProgramOptions.hpp"
#include "CVDemo.Image.ProgramOptionsHelper.hpp"
#include "CVDemo.Image.JoinProcessor.hpp"

using namespace cv;
using namespace std;
using namespace cvdemo::image;
// namespace po = boost::program_options;
// using namespace boost::filesystem;


int main(int argc, const char* argv[])
{
	// testing...
	string configFile = "../cvdemo.image.join.cfg";
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
		options.DisplayForegroundImageFile(cerr);
		options.DisplayForegroundImageFolder(cerr);
		options.DisplayOutputImageFolder(cerr);
		options.DisplayImageJoinOrientation(cerr);

		options.DisplayUsageInfo(cerr);

		system("pause");
		return EXIT_FAILURE;
	}

	vector<string> imageFiles;
	if (! options.GetForegroundImageFiles().empty()) {
		auto files = options.GetForegroundImageFiles();
		imageFiles.insert(imageFiles.end(), files.begin(), files.end());
	}
	if (options.GetForegroundImageFolder() != "") {
		auto fgFolder = options.GetForegroundImageFolder();
		// vector<string> fgFiles = get_all_file_names_within_folder(fgFolder);
		auto fgFiles = FileSystemHelper::findFiles(fgFolder);
		imageFiles.insert(imageFiles.end(), fgFiles.begin(), fgFiles.end());
	}

	try {
		auto outputFolder = options.GetOutputImageFolder();
		JoinProcessor::joinImageFiles(imageFiles, outputFolder);
	}
	catch (const exception& ex) {
		cerr << "Exception: " << ex.what() << endl;
	}

	// system("pause");
	return EXIT_SUCCESS;
}

