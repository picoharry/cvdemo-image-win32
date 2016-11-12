#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <boost/program_options.hpp>
#include "CVDemo.Image.ProgramOptions.hpp"

namespace po = boost::program_options;


namespace cvdemo
{
	namespace image
	{
		class ProgramOptionsHelper
		{
		private:
			ProgramOptionsHelper() {}
			ProgramOptionsHelper(ProgramOptionsHelper const&) = delete;
			void operator=(ProgramOptionsHelper const&) = delete;

		public:
			static ProgramOptionsHelper& getInstance()
			{
				static ProgramOptionsHelper instance;
				return instance;
			}

		public:
			void initialize(int argc, const char* argv[], std::string configFile = "")
			{
				options = ProgramOptions(argc, argv, configFile);
			}
			ProgramOptions getProgramOptions()
			{
				return options;
			}

		private:
			ProgramOptions options;

		};
	}
}
