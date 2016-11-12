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
			ProgramOptions(int argc, const char* argv[], std::string configFile = "");

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

				if (vm.count("foreground-image-file")) {
					os << "Foreground image file: " << vm["foreground-image-file"].as<std::string>() << std::endl;
				}
				if (vm.count("foreground-image-folder")) {
					os << "Foreground image folder: " << vm["foreground-image-folder"].as<std::string>() << std::endl;
				}

				if (vm.count("background-image-file")) {
					os << "Background image file: " << vm["background-image-file"].as<std::string>() << std::endl;
				}
				if (vm.count("background-image-folder")) {
					os << "Background image folder: " << vm["background-image-folder"].as<std::string>() << std::endl;
				}

				if (vm.count("output-image-folder")) {
					os << "Output image folder: " << vm["output-image-folder"].as<std::string>() << std::endl;
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
			void DisplayForegroundImageFile(std::ostream& os)
			{
				if (vm.count("foreground-image-file")) {
					os << "Foreground image file: " << vm["foreground-image-file"].as<std::string>() << std::endl;
				}
			}
			void DisplayForegroundImageFolder(std::ostream& os)
			{
				if (vm.count("foreground-image-folder")) {
					os << "Foreground image folder: " << vm["foreground-image-folder"].as<std::string>() << std::endl;
				}
			}

			void DisplayBackgroundImageFile(std::ostream& os)
			{
				if (vm.count("background-image-file")) {
					os << "Background image file: " << vm["background-image-file"].as<std::string>() << std::endl;
				}
			}
			void DisplayBackgroundImageFolder(std::ostream& os)
			{
				if (vm.count("background-image-folder")) {
					os << "Background image folder: " << vm["background-image-folder"].as<std::string>() << std::endl;
				}
			}

			void DisplayOutputImageFolder(std::ostream& os)
			{
				if (vm.count("output-image-folder")) {
					os << "Output image folder: " << vm["output-image-folder"].as<std::string>() << std::endl;
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
			std::string GetForegroundImageFile()
			{
				if (!isParsed) {
					_Parse();
				}
				if (!isValid) {
					throw std::exception("Options are invalid.");
				}
				return (vm.count("foreground-image-file") > 0) ? vm["foreground-image-file"].as<std::string>() : "";
			}
			std::string GetForegroundImageFolder()
			{
				if (!isParsed) {
					_Parse();
				}
				if (!isValid) {
					throw std::exception("Options are invalid.");
				}
				return (vm.count("foreground-image-folder") > 0) ? vm["foreground-image-folder"].as<std::string>() : "";
			}
			std::string GetBackgroundImageFile()
			{
				if (!isParsed) {
					_Parse();
				}
				if (!isValid) {
					throw std::exception("Options are invalid.");
				}
				return (vm.count("background-image-file") > 0) ? vm["background-image-file"].as<std::string>() : "";
			}
			std::string GetBackgroundImageFolder()
			{
				if (!isParsed) {
					_Parse();
				}
				if (!isValid) {
					throw std::exception("Options are invalid.");
				}
				return (vm.count("background-image-folder") > 0) ? vm["background-image-folder"].as<std::string>() : "";
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

		private:
			po::variables_map vm;
			po::options_description cmdline_options;
			po::options_description config_file_options;
			po::options_description visible_options;
			// po::options_description visible_options("Allowed options");
			std::vector<std::string> unrecognized;

		private:
			void _Initialize();
			void _Parse();
			bool _IsProgramOptionsValid()
			{
				if (vm.count("foreground-image-file") && vm.count("foreground-image-folder")) {
					return false;
				}
				if (vm.count("background-image-file") && vm.count("background-image-folder")) {
					return false;
				}
				if (vm.count("foreground-image-folder") && vm.count("background-image-folder")) {
					return false;
				}
				if ((vm.count("foreground-image-file") || vm.count("foreground-image-folder"))
					&& (vm.count("background-image-file") || vm.count("background-image-folder"))
					&& vm.count("output-image-folder")) {
					return true;
				}
				return false;
			}

		};
	}
}
