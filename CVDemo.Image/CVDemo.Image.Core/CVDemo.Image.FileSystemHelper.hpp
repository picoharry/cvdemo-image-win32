#pragma once

#include <string>
#include <vector>

namespace cvdemo
{
	namespace image
	{
		class FileSystemHelper
		{
		private:
			FileSystemHelper() {}

		public:
			// Returns the list of file paths for the given extension in a given folder.
			// extension: "png", etc...
			static std::vector<std::string> findFiles(std::string folderPath, std::string extension = "");

		};
	}
}
