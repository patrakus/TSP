#include "FileParser.h"
#include <sstream>


FileParser::FileParser(): size()
{
	//loadFile(path);
}


FileParser::~FileParser()
{
}


int** FileParser::loadFile(const std::string& path)
{
	
	std::string fileText;
	int** rangeArray;
	//int size;

	try
	{
		std::ifstream file(path);
		std::string line;

		if (file.is_open())
		{
			create2DArray(rangeArray, file, size);

			for (int i = 0; i < size; i++)
			{
				std::getline(file, line);
				rangeArray[i] = lineToNumbers(size, line);
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

void FileParser::create2DArray(int ** &pointer, std::ifstream& file, int& size)
{
	std::string line;

	std::getline(file, line);

	size = std::stoi(line);

	if (size != 0 && size > 0)
	{
		pointer = new int*[size];

		for (int i = 0; i < size; i++)
		{
			pointer[i] = new int[size];
		}
	}
}

int * FileParser::lineToNumbers(int size, const std::string & line)
{
	int* numbers = new int[size];

	std::stringstream ssInput(line);

	for (int i = 0; i < size; i++)
	{
		std::string number;

		if (!ssInput.eof())
		{
			ssInput >> number;

			if (number != "")
				numbers[i] = std::stoi(number);
		}
		else
		{
			numbers[i] = 0;
		}
	}

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
