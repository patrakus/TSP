#include "GeneticAlgorithm.h"
#include <ctime>
#include<iostream>


void writeAll(int* arr, int size);

GeneticAlgorithm::GeneticAlgorithm(int** & distanceMatrix, int genomSize) : 
	cityDistanceMatrix(distanceMatrix) ,
	cityIndex()
{
	generateGenoms(genomSize);
}


GeneticAlgorithm::~GeneticAlgorithm()
{
	for (size_t i = 0; i < cityIndex.size(); i++)
	{
		delete cityIndex.at(i);
	}
}

void GeneticAlgorithm::generateGenoms( int size)
{
	srand(time(NULL));

	for (int i = 0; i < size; i++)
	{
		int* newArray = new int[size]();
		initArray(newArray, size, -1);

		for (int j = 0; j < size; )
		{
			newArray[j] = rand() % size;

			if (!isDuplicateInArray(newArray, j + 1))
			{
				j++;
			}
		}

		writeAll(newArray, size);
		cityIndex.push_back(newArray);
	}
}

void GeneticAlgorithm::initArray(int * myArray, int size,int value)
{
	for (size_t i = 0; i < size; i++)
	{
		myArray[i] = value;
	}
}

bool GeneticAlgorithm::isDuplicateInArray(int * myArray, int size)
{
	int tmp = 0;

	for (size_t i = 0; i < size; i++)
	{
		tmp = myArray[i];

		for (size_t j = i + 1; j < size; j++)
		{
			//std::cout << "tmp has value: " << tmp << std::endl;
			//std::cout << "myArray[" << j << "] has value: " << myArray[j] << std::endl;

			if (myArray[j] == tmp)
			{
				return true;
			}
		}
	}

	return false;
}

void writeAll(int* arr, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << "---- " << arr[i] << std::endl;
	}
}