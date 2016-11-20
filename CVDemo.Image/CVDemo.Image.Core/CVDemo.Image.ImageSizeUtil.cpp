#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <opencv2/core.hpp>
#include "CVDemo.Image.StringHelper.hpp"
#include "CVDemo.Image.ImageSizeUtil.hpp"

using namespace std;
using namespace cv;


namespace cvdemo
{
	namespace image
	{
		Size ImageSizeUtil::parse(const string& line)
		{
			auto bf = _parse(line);
			Size size(bf.first, bf.second);
			return size;
		}

		pair<int, int> ImageSizeUtil::_parse(const string& line)
		{
			// Kernel size.
			int width;
			int height;
			if (!line.empty()) {
				auto trimmed = StringHelper::trim(line);
				if (!trimmed.empty()) {
					auto split1 = StringHelper::split(trimmed, CHAR_DIM_SEPARATOR);
					auto first = StringHelper::trimRight(split1.first);
					auto second = StringHelper::trimLeft(split1.second);
					// cerr << ">>>>>>>>>>>>> first = " << first << endl;
					// cerr << ">>>>>>>>>>>>> second = " << second << endl;
					try {
						width = stoi(first);
						height = stoi(second);
					}
					catch (const exception&)
					{
						// ignore.
					}
				}
			}
			auto pair = make_pair(width, height);
			return pair;
		}
	}
}
