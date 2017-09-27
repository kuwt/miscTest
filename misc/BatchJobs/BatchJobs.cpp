// BatchJobs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sstream>
#include <fstream>
#include <ostream>
#include <string>
#include <iostream> 

/*****************************************************

Define Batch Jobs

*********************************************************/
void AddPrefixPostfixBatch(
		std::string _inputFilePath, 
		std::string _outputFilePath,
		std::string _prefix,
		std::string _postfix)
{
	std::string inputFilePath = _inputFilePath;
	std::string outputFilePath = _outputFilePath;

	std::string prefix = _prefix;
	std::string postfix = _postfix;


	std::ifstream filestream(inputFilePath);
	std::ofstream outputFile(outputFilePath);
	std::string readline;

	while (std::getline(filestream, readline))
	{
		std::string NewString = prefix + readline + postfix;
		outputFile << NewString << std::endl;
	}
}

/*****************************************************

Select Batch jobs 

*********************************************************/
enum {
	Mode_AddPrefixPostfixBatch
};

int main()
{
	std::cout << "*********************************************" << std::endl;
	std::cout << "Please type mode number and hit return" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "AddPrefixPostfixBatch ---------------------- 1 " << std::endl;
	std::cout << "*********************************************" << std::endl;
	
	int mode;
	std::cin >> mode;

	if (mode == Mode_AddPrefixPostfixBatch)
	{

		/***************************************
		Sample:
		std::string inputFilePath = "C:\\temp\\a.txt";
		std::string outputFilePath = "C:\\temp\\b.txt";

		std::string prefix = "xcopy ";
		std::string postfix = " Dll\\debug /y ";
		**************************************/
		char input[300];
		std::cout << "inputFilePath?" << std::endl;
		std::cin.getline(input, sizeof(input));
		std::string inputPath(input);

		std::cout << "OutputFilePath?" << std::endl;
		std::cin.getline(input, sizeof(input));
		std::string OutputPath(input);

		std::cout << "prefix?" << std::endl;
		std::cin.getline(input, sizeof(input));
		std::string prefix(input);

		std::cout << "postfix?" << std::endl;
		std::cin.getline(input, sizeof(input));
		std::string postfix(input);

		AddPrefixPostfixBatch(inputPath,
			OutputPath,
			prefix,
			postfix);
	}
	
	return 0;
}
