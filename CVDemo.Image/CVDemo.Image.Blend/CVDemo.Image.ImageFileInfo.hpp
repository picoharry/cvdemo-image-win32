#pragma once

#include <string>
#include <vector>


namespace cvdemo
{
	namespace image
	{
		class ImageFileInfo
		{
		public:
			ImageFileInfo(std::string& filePath, float blendingWeight)
				: path(filePath), weight(blendingWeight)
			{
			}

		private:
			const std::string path;  // name? absolute vs relative path?
			const float weight;      // blending weight.

		public:
			const std::string GetPath() const
			{
				return path;
			}
			const float GetWeight() const
			{
				return weight;
			}

			// friend std::ostream& operator<< (std::ostream& os, const ImageFileInfo& info);

		};

    }

}

std::ostream& operator<< (std::ostream& os, const cvdemo::image::ImageFileInfo& info);
