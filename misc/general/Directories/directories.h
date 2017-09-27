#pragma once 

#include <string>
#include <vector>


int listAllFilesPathsFromDir(const std::string& dirPath,
	const std::string &extension,
	std::vector<std::string> &path);

bool CheckIfFilePathContainSubPath(const std::string& FilePath,
	const std::string &SubPath);