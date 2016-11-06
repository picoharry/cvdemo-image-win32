#include "stdafx.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/video.hpp>
#include <stdio.h>
#include <sstream>
#include <stdexcept>
#include <boost/program_options.hpp>
#include "CVDemo.Image.ProgramOptions.hpp"

using namespace cv;
using namespace std;
namespace po = boost::program_options;


namespace cvdemo
{
	namespace image
	{
		// http://www.boost.org/doc/libs/1_62_0/doc/html/program_options.html

		ProgramOptions::ProgramOptions(int cmdlineArgc, const char* cmdlineArgv[], std::string configFile)
			: cmdlineArgc(cmdlineArgc), cmdlineArgv(cmdlineArgv), configFilePath(configFile)
			// foregroundImageFiles(), backgroundImageFiles()
		{
			_Initialize();
		}
		void ProgramOptions::_Initialize()
		{
			// Declare a group of options that will be 
			// allowed only on command line
			po::options_description generic("Generic options");
			generic.add_options()
				("help,H", "Produce help message")
				("version,V", "Print version string")
				("options,O", "Print input options")
				;

			// Declare a group of options that will be 
			// allowed both on command line and in
			// config file
			po::options_description config("Configuration");
			config.add_options()
				// Why is the value type vector<string>, not string?????
				//("foreground-image,F", po::value<string>()->multitoken(), "Foreground image file")
				//("background-image,B", po::value<string>()->multitoken(), "Background image file")
				("foreground-image,F", po::value<vector<string>>()->multitoken(), "Foreground image file")
				("background-image,B", po::value<vector<string>>()->multitoken(), "Background image file")
				;

			// Hidden options, will be allowed both on command line and
			// in config file, but will not be shown to the user.
			float scale_factor;
			po::options_description hidden("Hidden options");
			hidden.add_options()
				("scale-factor,S", po::value<float>(&scale_factor)->default_value(1.0f), "Scale factor (default: 1.0)")
				;


			cmdline_options.add(generic).add(config).add(hidden);
			config_file_options.add(config).add(hidden);
			// visible_options = "Allowed options";   // ???
			visible_options.add(generic).add(config);
		}
		void ProgramOptions::_Parse()
		{
			// ???
		    // po::store(po::command_line_parser(cmdlineArgc, cmdlineArgv).options(cmdline_options).run(), vm);
			try {
				// po::store(po::parse_command_line(cmdlineArgc, cmdlineArgv, cmdline_options), vm);
				// Ignore unknown options???
				po::parsed_options cmdlineParsed = po::command_line_parser(cmdlineArgc, cmdlineArgv).options(cmdline_options).allow_unregistered().run();
				po::store(cmdlineParsed, vm);

				unrecognized = po::collect_unrecognized(cmdlineParsed.options, po::collect_unrecognized_mode::include_positional);
				//for (auto &i : unrecognized) {
				//	cout << "Unrecognised: " << i << endl;
				//}
			}
			catch (const exception& e) {   // ignore
				cerr << e.what() << endl;
				// isParsed = true;
				hasSyntacticError = true;
				// isValid = false;
				return;
			}
			//catch (...)
			//{
			//	// testing...
			//	cout << "catch all" << endl;
			//	cerr << "catch all" << endl;

			//}
			// ???
			if (configFilePath.size() > 0) {
				try {
					// temporary
					// cerr << "Parsing config file: " << configFilePath << "..." << endl;
					// temporary
					po::parsed_options configParsed = po::parse_config_file<char>(configFilePath.c_str(), config_file_options, true);  // allow_unregistered == true.
					// po::store(configParsed, vm, true);
					po::store(configParsed, vm, false);   // ???
				}
				catch (const exception& e) {   // ignore
					cerr << e.what() << endl;
					// If configFile arg is specified, and it's not valid (e.g., the file does not exist or the file is invalid, etc.),
					//  then we consider it as "syntactic" error.
					hasSyntacticError = true;
					// isValid = false;
				}
			}
			// ???
			po::notify(vm);



			if (vm.count("help")) {
				// cout << visible_options << endl;
				// isParsed = true;
				isForUsageInfo = true;
				// return;   // continue parsing???
			}
			if (vm.count("version")) {
				// cout << "version..." << endl;
				// isParsed = true;
				isForVersionInfo = true;
				// return;   // continue parsing???
			}
			if (vm.count("options")) {
				// cout << "options..." << endl;
				// isParsed = true;
				isForOptionsDisplay = true;
				// return;   // continue parsing???
			}

			isParsed = true;
			// Required params.
			if (vm.count("foreground-image") && vm.count("background-image")) {
				isValid = true;
			}
			else {
				isValid = false;
			}


			// For debugging...


			//cout << "Scale factor was set to " << vm["scale-factor"].as<float>() << "." << endl;

			//if (vm.count("foreground-image")) {
			//	// ???
			//	// cout << "Foreground image files: " << vm["foreground-image"].as<vector<string>>() << "." << endl;
			//	cout << "Foreground image file count: " << vm["foreground-image"].as<vector<string>>().size() << "." << endl;
			//	cout << "Foreground image files: " << endl;
			//	for (auto &i : vm["foreground-image"].as<vector<string>>()) {
			//		cout << i << endl;
			//	}

			//	//const string arr[] = {"aa.png", "bb.png"};
			//	//vector<string> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
			//	//// count << vec.at<string>(0) << endl;
			//	//for (auto &i : vec) {
			//	//	std::cout << i << endl;
			//	//}


			//}
			//else {
			//	// error? Use default value????
			//	cout << "Foreground image files not specified." << endl;
			//}
			//if (vm.count("background-image")) {
			//	// ???
			//	//cout << "Background image files: " << vm["background-image"].as<vector<string>>() << "." << endl;
			//	cout << "Background image file count: " << vm["background-image"].as<vector<string>>().size() << "." << endl;
			//	cout << "Background image files: " << endl;
			//	for (auto &i : vm["background-image"].as<vector<string>>()) {
			//		cout << i << endl;
			//	}
			//}
			//else {
			//	// error? Use default value????
			//	cout << "Background image files not specified." << endl;
			//}



		}

	}
}
