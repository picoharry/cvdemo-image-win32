#pragma once

#include <string>

namespace cvdemo
{
	namespace image
	{
		enum TargetImageMode
		{
			unknown = 0,
			bounding = 1,
			overlap = 2
		};

		class TargetImageModes
		{
		public:
			static std::string ToString(const TargetImageMode mode)
			{
				switch (mode) {
				case TargetImageMode::bounding:
					return "bounding";
				case TargetImageMode::overlap:
					return "overlap";
				default:
				case TargetImageMode::unknown:
					return "unknown";
				}
			}
			static TargetImageMode FromString(const std::string str)
			{
				if (str == "bounding") {
					return TargetImageMode::bounding;
				}
				else if (str == "overlap") {
			    	return TargetImageMode::overlap;
				}
				else {
					return TargetImageMode::unknown;
				}
			}
		};
	}
}
