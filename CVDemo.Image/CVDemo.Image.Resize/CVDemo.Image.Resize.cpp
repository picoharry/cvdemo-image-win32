// CVDemo.Image.Resize.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/program_options.hpp>

using namespace cv;
using namespace std;
namespace po = boost::program_options;


int main(int argc, const char* argv[])
{
	// http://www.boost.org/doc/libs/1_62_0/doc/html/program_options.html


	// Declare the supported options.
	float scale_factor;
	po::options_description desc("Allowed options");
	desc.add_options()
		("version,V", "Print version string")
		("help,H", "Produce help message")
		("scale-factor,S", po::value<float>(&scale_factor)->default_value(0.5f), "Scale factor (default: 0.5)")
		("source-image,I", po::value< vector<string> >(), "Source image file")
		;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		cout << desc << endl;
		return 1;
	}
	if (vm.count("version")) {
		cout << "version..." << endl;
		return 1;
	}

	cout << "Scale factor was set to " << vm["scale-factor"].as<float>() << "." << endl;
	if (vm.count("source-image")) {
		// ???
		//cout << "Source image files: " << vm["source-image"].as<vector<string>>() << "." << endl;
	} else {
		// error? Use default value????
		cout << "Source image files not specified." << endl;
	}






	system("pause");
    return 0;
}

