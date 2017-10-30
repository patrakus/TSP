#include "GeneticAlgorithm.h"
#include <ctime>
#include<iostream>


void writeAll(int* arr, int size);
int returnNumber(int a, int b, int** array2D);

GeneticAlgorithm::GeneticAlgorithm(int** & distanceMatrix, int genomSize, int populationSize) :
	cityDistanceMatrix(distanceMatrix) , m_size(genomSize), cityIndex()
{
	generateGenoms(genomSize, populationSize);
}


GeneticAlgorithm::~GeneticAlgorithm()
{
	for (size_t i = 0; i < cityIndex.size(); i++)
	{
		delete cityIndex.at(i);
	}

	delete marks;
}

void GeneticAlgorithm::generateGenoms( int size, int populationSize)
{
	srand(time(NULL));

	for (int i = 0; i < populationSize; i++)
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

		//writeAll(newArray, size);
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

void GeneticAlgorithm::markPopulations()
{
	marks = new int[m_size]();

	int tmp = -1;
	int a, b;

	for (size_t i = 0; i < cityIndex.size(); i++)
	{
		for (size_t j = 0; j < m_size; j++)
		{
			if (j + 1 < m_size)
			{
				a = cityIndex.at(i)[j];
				b = cityIndex.at(i)[j + 1];

				tmp = returnNumber(a, b, cityDistanceMatrix);

				marks[i] += tmp;
			}
			else
			{
				a = cityIndex.at(i)[j];
				b = cityIndex.at(i)[0];

				tmp = returnNumber(a, b, cityDistanceMatrix);

				marks[i] += tmp;
			}
		}

		std::cout << "Mark: " << marks[i] << std::endl;
	}
}

void writeAll(int* arr, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << "---- " << arr[i] << std::endl;
	}
}

int returnNumber(int a, int b, int** array2D)
{
	if (a > b)
		return array2D[a][b];
	else
		return array2D[b][a];
}