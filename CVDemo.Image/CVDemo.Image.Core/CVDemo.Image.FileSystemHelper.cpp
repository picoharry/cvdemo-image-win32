#include <string>
#include <vector>
#include "CVDemo.Image.FileSystemHelper.hpp"

// temporary
#include <Windows.h>

using namespace std;


namespace cvdemo
{
	namespace image
	{
		// Windows only.
		vector<string> FileSystemHelper::findFiles(string folderPath, string extension)
		{
			// file paths.
			vector<string> files;
			string glob = "/*";
			if (!extension.empty()) {
				glob += "." + extension;
			}
			string searchPath = folderPath + glob;

			WIN32_FIND_DATAA fd;
			HANDLE hFind = ::FindFirstFileA(searchPath.c_str(), &fd);   // ????
			if (hFind != INVALID_HANDLE_VALUE) {
				do {
					// read all (real) files in current folder
					// , delete '!' read other 2 default folder . and ..
					if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
						// names.push_back(fd.cFileName);   // ????
						files.push_back(folderPath + "/" + fd.cFileName);   // ????
					}
				} while (::FindNextFileA(hFind, &fd));
				::FindClose(hFind);
			}

			// tbd:
			return files;
		}
	}
}
