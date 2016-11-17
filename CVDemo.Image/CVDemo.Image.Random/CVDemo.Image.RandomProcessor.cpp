#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <opencv2/imgcodecs.hpp>
#include "CVDemo.Image.ProgramOptions.hpp"
#include "CVDemo.Image.ProgramOptionsHelper.hpp"
#include "CVDemo.Image.RandomProcessor.hpp"

using namespace cv;
using namespace std;


namespace cvdemo
{
	namespace image
	{
		string RandomProcessor::getOutputFilename(const string fgFilePath, const string bgFilePath)
		{
			//auto fgFN = string(find_if(fgFilePath.rbegin(), fgFilePath.rend(), "\\").base(), fgFilePath.end());
			//auto fgPivot = std::find(fgFN.rbegin(), fgFN.rend(), '.');
			//auto fgBase = (fgPivot == fgFN.rend()) ? fgFN : string(fgFN.begin(), fgPivot.base() - 1);
			auto fgFN = fgFilePath.substr(fgFilePath.find_last_of("/\\") + 1);
			auto fgDot = fgFN.find_last_of('.');
			auto fgBase = fgFN.substr(0, fgDot);

			//auto bgFN = string(find_if(bgFilePath.rbegin(), bgFilePath.rend(), "\\").base(), bgFilePath.end());
			//auto bgPivot = std::find(bgFN.rbegin(), bgFN.rend(), '.');
			//auto bgBase = (bgPivot == bgFN.rend()) ? bgFN : string(bgFN.begin(), bgPivot.base() - 1);
			//// auto bgExtension = (bgPivot == bgFN.rend()) ? "" : string(bgPivot.base() + 1, bgFN.end());  // ???
			//auto bgExtension = "png";   // tbd:
			auto bgFN = bgFilePath.substr(bgFilePath.find_last_of("/\\") + 1);
			auto bgDot = bgFN.find_last_of('.');
			auto bgBase = bgFN.substr(0, bgDot);
			auto bgExtension = bgFN.substr(bgDot + 1);

			string outputFN = fgBase + "-on-" + bgBase + "." + bgExtension;
			cout << "Output image file name: " << outputFN << endl;

			return outputFN;
		}

	}
}
