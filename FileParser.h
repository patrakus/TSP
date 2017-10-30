#pragma once
#include <fstream>
#include <iostream>
#include <string>


class FileParser
{
public:
	FileParser();
	~FileParser();

	int** loadFile(const std::string& path);
	int size;

private:

	void create2DArray(int** &pointer, std::ifstream& file, int& size);
	int* lineToNumbers(int size, const std::string& line);
	//std::string* splitString(const std::string& line);

	
};

