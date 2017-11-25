#pragma once
#include <fstream>
#include <string>
#include <memory>
#include <vector>


class FileParser
{
	std::shared_ptr<std::vector<std::vector<int>>> rangeArray;

public:
	FileParser();
	~FileParser();

	std::shared_ptr<std::vector<std::vector<int>>> loadFile(const std::string& path);
	int size;

private:

	void create2DArray(std::ifstream& file);
	std::vector<int> lineToNumbers(int size, const std::string& line);
	//std::string* splitString(const std::string& line);

	
};

