// CVDemo.Image.Mix.cpp : Defines the entry point for the console application.
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
#include "CVDemo.Image.MixProcessor.hpp"

// temporary
#include <Windows.h>


using namespace cv;
using namespace std;
using namespace cvdemo::image;
// namespace po = boost::program_options;
// using namespace boost::filesystem;


// To be deleted.
vector<string> get_all_file_names_within_folder(string folder)
{
	vector<string> names;

	// ????
	string search_path = folder + "/*.png";
	WIN32_FIND_DATAA fd;
	HANDLE hFind = ::FindFirstFileA(search_path.c_str(), &fd);   // ????
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				// names.push_back(fd.cFileName);   // ????
				names.push_back(folder + "/" + fd.cFileName);   // ????
			}
		} while (::FindNextFileA(hFind, &fd));
		::FindClose(hFind);
	}

	//for (auto i = directory_iterator(folder); i != directory_iterator(); i++)
	//{
	//	if (!is_directory(i->path()))
	//	{
	//		names.push_back(i->path().filename().string());
	//	}
	//}

	return names;
}


int main(int argc, const char* argv[])
{
	// testing...
	string configFile = "../cvdemo.image.mix.cfg";
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
		options.DisplayBackgroundImageFile(cerr);
		options.DisplayBackgroundImageFolder(cerr);
		options.DisplayOutputImageFolder(cerr);

		options.DisplayUsageInfo(cerr);

		system("pause");
		return EXIT_FAILURE;
	}

	if (options.GetForegroundImageFile() != "" && options.GetBackgroundImageFile() != "") {
		MixProcessor::mixImages(options.GetForegroundImageFile(), options.GetBackgroundImageFile(), options.GetOutputImageFolder());
	}
	else {
		if (options.GetForegroundImageFolder() != "" && options.GetBackgroundImageFile() != "") {
			auto fgFolder = options.GetForegroundImageFolder();
			// vector<string> fgFiles = get_all_file_names_within_folder(fgFolder);
			vector<string> fgFiles = FileSystemHelper::findFiles(fgFolder);
			MixProcessor::mixImages(fgFiles, options.GetBackgroundImageFile(), options.GetOutputImageFolder());
		}
		else if (options.GetForegroundImageFile() != "" && options.GetBackgroundImageFolder() != "") {
			auto bgFolder = options.GetBackgroundImageFolder();
			// vector<string> bgFiles = get_all_file_names_within_folder(bgFolder);
			vector<string> bgFiles = FileSystemHelper::findFiles(bgFolder);
			MixProcessor::mixImages(options.GetForegroundImageFile(), bgFiles, options.GetOutputImageFolder());
		}
		else {
			// ????
		}
	}

	system("pause");
	return EXIT_SUCCESS;
}

