#include "FileParser.h"
#include <sstream>
#include <iostream>


FileParser::FileParser() : size(), rangeArray()
{
	//loadFile(path);
}


FileParser::~FileParser()
{
}


std::shared_ptr<std::vector<std::vector<int>>> FileParser::loadFile(const std::string& path)
{
	//int** rangeArray = 0;
	//int size;

	try
	{
		std::ifstream file(path);
		std::string line;

		if (file.is_open())
		{
			create2DArray(file);

			for (int i = 0; i < size; i++)
			{
				std::getline(file, line);

				rangeArray->push_back( lineToNumbers(size, line));
			}
		}
		else if (file.bad())
		{
			std::cerr << "Missing file: " << path << std::endl;
		}
		/*else
		{
			throw new std::exception("File is not open");
		}*/

	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return rangeArray;
}

void FileParser::create2DArray(std::ifstream& file)
{
	std::string line;

	std::getline(file, line);

	size = std::stoi(line);



	if (size != 0 && size > 0)
	{
		std::shared_ptr<std::vector<std::vector<int>>> tmp(new std::vector<std::vector<int>>);
		//tmp->resize(size);

		/*for (int i = 0; i < size; i++)
		{
			tmp.get[i].resize(size);
		}*/

		rangeArray = tmp;
	}
}

std::vector<int> FileParser::lineToNumbers(int size, const std::string & line)
{
	std::vector<int> numbers;

	std::stringstream ssInput(line);

	for (int i = 0; i < size; i++)
	{
		std::string number;

		if (!ssInput.eof())
		{
			ssInput >> number;

			if (number != "")
				numbers.push_back(std::stoi(number));
			else
				numbers.push_back(0);
		}
		else
		{
			numbers.push_back(0);
		}
	}

	//numbers.shrink_to_fit();

	//std::cout << numbers.size() << std::endl;

	return numbers;
}

/*std::string * FileParser::splitString(const std::string & line)
{
	

	int numbersCounter = 1;

	for (long i = 0; i < line.length(); i++)
	{
		if (line[i] == ' ')
			numbersCounter++;
	}

	std::string* abc = new std::string[numbersCounter];

	for (int i = 0; i < numbersCounter && ssInput.good(); i++)
	{
		ssInput >> abc[i];
	}

	return abc;
}*/
