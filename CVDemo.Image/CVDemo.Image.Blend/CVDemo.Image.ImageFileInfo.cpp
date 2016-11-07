#include "stdafx.h"
#include <stdio.h>
#include <sstream>
#include <stdexcept>
#include "CVDemo.Image.ImageFileInfo.hpp"

using namespace std;

namespace cvdemo
{
	namespace image
	{
		//std::ostream& operator<< (std::ostream& os, const ImageFileInfo& info)
		//{
		//	os << info.GetPath() << ":" << info.GetWeight();
		//	return os;
		//}
	}
}

std::ostream& operator<< (std::ostream& os, const cvdemo::image::ImageFileInfo& info)
{
	os << info.GetPath() << ":" << info.GetWeight();
	return os;
}
