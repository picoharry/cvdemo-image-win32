#include "stdafx.h"
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
			// string output_image_mode;
			// TargetImageMode output_image_mode = TargetImageMode::unknown;
			config.add_options()
				// Why is the value type vector<string>, not string?????
				// ("output-image-mode,M", po::value<string>(&output_image_mode)->default_value(TargetImageModes::ToString(TargetImageMode::bounding)), "Output image mode (default: bounding)")
				("output-image-mode,M", po::value<string>()->default_value(TargetImageModes::ToString(TargetImageMode::bounding)), "Output image mode (default: bounding)")
				("image-file,I", po::value<vector<string>>()->multitoken(), "Image file")
				("blending-weight,W", po::value<vector<float>>()->multitoken(), "Blending weight")
				;

			// Hidden options, will be allowed both on command line and
			// in config file, but will not be shown to the user.
			// bool resize_allowed;
			po::options_description hidden("Hidden options");
			hidden.add_options()
				("resize-allowed,R", po::value<bool>()->default_value(false), "Resize-allowed (default: false)")
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


			// temporary

			// int fileCount = vm.count("image-file");
			// int weightCount = vm.count("blending-weight");
			if (vm.count("image-file") > 0) {

				auto& files = vm["image-file"].as<vector<string>>();
				int fileCount = files.size();
				int weightCount = 0;
				vector<float> weights;
				if (vm.count("blending-weight") > 0) {
					weights = vm["blending-weight"].as<vector<float>>();
					weightCount = weights.size();
				}
				if (weightCount > fileCount) {
					weightCount = fileCount;
				}
				float remWeight = 0.0f;
				float weightSum = 0.0f;
				for (auto a = 0; a < weightCount;a++) {
					weightSum += weights[a];   // weights[a] >= 0.0f
				}
				// tbd: validate weightSum?
				// 0.0f <= weightSum <= 1.0f.
				if (weightCount < fileCount) {
					remWeight = (1.0f - weightSum) / (fileCount - weightCount);
				}


				// ???
				// cout << "File count: " << fileCount << "." << endl;
				for (auto i = 0; i < fileCount; i++) {
					auto name = files[i];
					auto weight = 0.0f;
					if (i < weightCount) {
						weight = weights[i];
					}
					else {
						weight = remWeight;
					}
					auto info = ImageFileInfo(name, weight);
					imageFileInfos.push_back(info);
				}
			}



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
			// if (vm.count("image-file")) {   // && vm.count("blending-weight")
		    if (imageFileInfos.size() > 0) {
					isValid = true;
			}
			else {
				isValid = false;
			}


		}

	}
}
