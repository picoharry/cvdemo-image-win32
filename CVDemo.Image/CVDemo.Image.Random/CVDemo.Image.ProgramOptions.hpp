#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <boost/program_options.hpp>

namespace po = boost::program_options;


namespace cvdemo
{
	namespace image
	{
		class ProgramOptions
		{
		public:
			ProgramOptions() {}
			ProgramOptions(int argc, const char* argv[], std::string configFile = "");
			void operator=(ProgramOptions const&);

		private:
			int cmdlineArgc;
			const char** cmdlineArgv;
			std::string configFilePath;

		private:
			bool isParsed = false;
			// bool isForInfoOnly = false;
			bool isForUsageInfo = false;
			bool isForVersionInfo = false;
			bool isForOptionsDisplay = false;   // true == like "echo" for options.
			// These flags make sense only if isParsed == true.
			bool hasSyntacticError = false;
			bool isValid = false;
		public:
			//bool IsInitialized()
			//{
			//	return isInitialized;
			//}
			//bool IsParsed()
			//{
			//	return isParsed;
			//}
			bool IsForInfoOnly()
			{
				if (!isParsed) {
					_Parse();
				}
				return isForUsageInfo || isForVersionInfo || isForOptionsDisplay;
			}
			bool IsForUsageInfo()
			{
				if (!isParsed) {
					_Parse();
				}
				return isForUsageInfo;
			}
			bool IsForVersionInfo()
			{
				if (!isParsed) {
					_Parse();
				}
				return isForVersionInfo;
			}
			bool IsForOptionsDisplay()
			{
				if (!isParsed) {
					_Parse();
				}
				return isForOptionsDisplay;
			}
			bool HasSyntacticError()
			{
				if (!isParsed) {
					_Parse();
				}
				return hasSyntacticError;
			}
			bool IsValid()
			{
				if (HasSyntacticError()) {
					return false;
				}
				else {
					return isValid;
				}
			}

		public:
			void DisplayUsageInfo(std::ostream& os)
			{
				//if (!isParsed) {
				//	_Parse();
				//}
				os << visible_options << std::endl;
			}
			void DisplayInputOptions(std::ostream& os)
			{
				if (!isParsed) {
					_Parse();
				}

				os << "Input options parsed:" << std::endl;
				os << "Has syntax error? " << hasSyntacticError << std::endl;
				os << "Is orverall valid? " << isValid << std::endl;


				std::vector<std::string> unrecognized = GetUnrecognizedArgs();
				for (auto &i : unrecognized) {
					os << "Unrecognized: " << i << std::endl;
				}

				// ???
				//for (auto &a : vm) {
				//	os << "Name = " << a.first << "; Value = " << a.second.value << std::endl;
				//}

				// tbd:
				// empty string means use thee default type (e.g., "png") ???
				os << "Output image type is set to " << vm["output-image-type"].as<std::string>() << "." << std::endl;

				if (vm.count("image-size")) {
					// os << "Image size: " << vm["image-size"].as<std::string>() << std::endl;
					os << "Image size: " << imageSize << std::endl;
				}

				if (vm.count("output-image-folder")) {
					os << "Output image folder: " << vm["output-image-folder"].as<std::string>() << std::endl;
				}

				if (vm.count("element-weight-dots")) {
					os << "Random element weight for dots: " << vm["element-weight-dots"].as<float>() << std::endl;
				}
				if (vm.count("element-weight-lines")) {
					os << "Random element weight for lines: " << vm["element-weight-lines"].as<float>() << std::endl;
				}
				if (vm.count("element-weight-rectangles")) {
					os << "Random element weight for rectangles: " << vm["element-weight-rectangles"].as<float>() << std::endl;
				}
				if (vm.count("element-weight-circles")) {
					os << "Random element weight for circles: " << vm["element-weight-circles"].as<float>() << std::endl;
				}

			}
			std::vector<std::string> GetUnrecognizedArgs()
			{
				if (!isParsed) {
					_Parse();
				}
				return unrecognized;
			}

		public:
			// For debugging purpoes:
			void DisplayUnrecognizedArgs(std::ostream& os)
			{
				std::vector<std::string> unrecognized = GetUnrecognizedArgs();
				for (auto &i : unrecognized) {
					os << "Unrecognized: " << i << std::endl;
				}
			}
			void DisplayOutputImageType(std::ostream& os)
			{
				os << "Output image type is set to " << vm["output-image-type"].as<std::string>() << "." << std::endl;
			}

			void DisplayImageSize(std::ostream& os)
			{
				if (vm.count("image-size")) {
					// os << "Image size: " << vm["image-size"].as<std::string>() << std::endl;
					os << "Image size: " << imageSize << std::endl;
				}
			}

			void DisplayOutputImageFolder(std::ostream& os)
			{
				if (vm.count("output-image-folder")) {
					os << "Output image folder: " << vm["output-image-folder"].as<std::string>() << std::endl;
				}
			}

			void DisplayElementWeightForDots(std::ostream& os)
			{
				if (vm.count("element-weight-dots")) {
					os << "Random element weight for dots: " << vm["element-weight-dots"].as<float>() << std::endl;
				}
			}
			void DisplayElementWeightForLines(std::ostream& os)
			{
				if (vm.count("element-weight-lines")) {
					os << "Random element weight for lines: " << vm["element-weight-lines"].as<float>() << std::endl;
				}
			}
			void DisplayElementWeightForRectangles(std::ostream& os)
			{
				if (vm.count("element-weight-rectangles")) {
					os << "Random element weight for rectangles: " << vm["element-weight-rectangles"].as<float>() << std::endl;
				}
			}
			void DisplayElementWeightForCircles(std::ostream& os)
			{
				if (vm.count("element-weight-circles")) {
					os << "Random element weight for circles: " << vm["element-weight-circles"].as<float>() << std::endl;
				}
			}

		public:
			std::string GetOutputImageType()
			{
				if (!isParsed) {
					_Parse();
				}
				if (!isValid) {
					throw std::exception("Options are invalid.");
				}
				return vm["output-image-type"].as<std::string>();
			}

			//std::string GetImageSize()
			//{
			//	if (!isParsed) {
			//		_Parse();
			//	}
			//	if (!isValid) {
			//		throw std::exception("Options are invalid.");
			//	}
			//	return (vm.count("image-size") > 0) ? vm["image-size"].as<std::string>() : "";
			//}
			cv::Size GetImageSize()
			{
				if (!isParsed) {
					_Parse();
				}
				if (!isValid) {
					throw std::exception("Options are invalid.");
				}
				return imageSize;
			}

			std::string GetOutputImageFolder()
			{
				if (!isParsed) {
					_Parse();
				}
				if (!isValid) {
					throw std::exception("Options are invalid.");
				}
				return (vm.count("output-image-folder") > 0) ? vm["output-image-folder"].as<std::string>() : "";
			}

			float GetElementWeightForDots()
			{
				if (!isParsed) {
					_Parse();
				}
				if (!isValid) {
					throw std::exception("Options are invalid.");
				}
				return (vm.count("element-weight-dots") > 0) ? vm["element-weight-dots"].as<float>() : 0.0f;
			}
			float GetElementWeightForLines()
			{
				if (!isParsed) {
					_Parse();
				}
				if (!isValid) {
					throw std::exception("Options are invalid.");
				}
				return (vm.count("element-weight-lines") > 0) ? vm["element-weight-lines"].as<float>() : 0.0f;
			}
			float GetElementWeightForRectangles()
			{
				if (!isParsed) {
					_Parse();
				}
				if (!isValid) {
					throw std::exception("Options are invalid.");
				}
				return (vm.count("element-weight-rectangles") > 0) ? vm["element-weight-rectangles"].as<float>() : 0.0f;
			}
			float GetElementWeightForCircles()
			{
				if (!isParsed) {
					_Parse();
				}
				if (!isValid) {
					throw std::exception("Options are invalid.");
				}
				return (vm.count("element-weight-circles") > 0) ? vm["element-weight-circles"].as<float>() : 0.0f;
			}

		private:
			po::variables_map vm;
			po::options_description cmdline_options;
			po::options_description config_file_options;
			po::options_description visible_options;
			// po::options_description visible_options("Allowed options");
			std::vector<std::string> unrecognized;
			// Variables stored outside vm
			cv::Size imageSize;
			// ...

		private:
			void _Initialize();
			void _Parse();
			bool _IsProgramOptionsValid()
			{
				if (vm.count("output-image-folder")
					&& vm.count("image-size")) {   // tbd: check if imageSize > Size(0,0) ???
					return true;
				}
				return false;
			}

		};
	}
}
