#include <boost/filesystem.hpp>
#include <string>
#include <vector>


// return the filenames of all files that have the specified extension
// in the specified directory and all subdirectories
void get_all_file(const ::boost::filesystem::path& root,
	const std::string& ext,
	std::vector<::boost::filesystem::path>& ret)
{
	if (!::boost::filesystem::exists(root) || !::boost::filesystem::is_directory(root)) return;

	::boost::filesystem::recursive_directory_iterator it(root);
	::boost::filesystem::recursive_directory_iterator endit;

	while (it != endit)
	{
		if (::boost::filesystem::is_regular_file(*it) && it->path().extension() == ext)
		{
			ret.push_back(it->path());
		}
		++it;
	}
}


int listAllFilesPathsFromDir(const std::string& dirPath, 
	const std::string &extension, 
	std::vector<std::string> &path)
{
	path.clear();
	std::vector<::boost::filesystem::path> dataPaths;

	{
		std::vector<::boost::filesystem::path> dataPathsPerExt;

		dataPathsPerExt.clear();
		get_all_file(dirPath,
			extension,
			dataPaths);
		dataPaths.insert(dataPaths.end(), dataPathsPerExt.begin(), dataPathsPerExt.end());

	}
	for (int i = 0; i < dataPaths.size(); ++i)
	{
		std::string dataPath = dataPaths.at(i).string();
		path.push_back(dataPath);
	}

	return 0;
}

bool CheckIfFilePathContainSubPath(const std::string& FilePath,
	const std::string &SubPath)
{
	int wildcard_pos = FilePath.find(SubPath);
	if (wildcard_pos != std::string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}

}