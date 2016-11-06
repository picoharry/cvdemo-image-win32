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
				// return isForInfoOnly;
				return IsForUsageInfo() || IsForVersionInfo();
			}
			bool IsForUsageInfo()
			{
				if (! isParsed) {
					_Parse();
				}
				return isForUsageInfo;
			}
			bool IsForVersionInfo()
			{
				if (! isParsed) {
					_Parse();
				}
				return isForVersionInfo;
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
			void DisplayScaleFactor(std::ostream& os)
			{
				os << "Scale factor is set to " << vm["scale-factor"].as<float>() << "." << std::endl;
			}
			void DisplayForegroundImageFiles(std::ostream& os)
			{
				// std::vector<std::string> files = GetForegroundImageFiles();
				std::vector<std::string> files;
				if (vm.count("foreground-image")) {
					files = vm["foreground-image"].as<std::vector<std::string>>();
				}
				for (auto &i : files) {
					os << "Foreground file: " << i << std::endl;
				}
			}
			void DisplayBackgroundImageFiles(std::ostream& os)
			{
				// std::vector<std::string> files = GetBackgroundImageFiles();
				std::vector<std::string> files;
				if (vm.count("background-image")) {
					files = vm["background-image"].as<std::vector<std::string>>();
				}
				for (auto &i : files) {
					os << "Background file: " << i << std::endl;
				}
			}

		//private:
		//	// float scaleFactor = 1.0f;
		//	// std::vector<std::string> foregroundImageFiles;
		//	// std::vector<std::string> backgroundImageFiles;
		public:
			float GetScaleFactor()
			{
				if (! isParsed) {
					_Parse();
				}
				if (!isValid) {
					throw std::exception("Options are invalid.");
				}
				// return scaleFactor;
				return vm["scale-factor"].as<float>();
			}
			std::vector<std::string> GetForegroundImageFiles()
			{
				if (! isParsed) {
					_Parse();
				}
				if (!isValid) {
					throw std::exception("Options are invalid.");
				}
				// return foregroundImageFiles;
				return vm["foreground-image"].as<std::vector<std::string>>();
			}
			std::vector<std::string> GetBackgroundImageFiles()
			{
				if (! isParsed) {
					_Parse();
				}
				if (!isValid) {
					throw std::exception("Options are invalid.");
				}
				// return backgroundImageFiles;
				return vm["background-image"].as<std::vector<std::string>>();
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

		};
	}
}
