#pragma once
#include <vector>

class GeneticAlgorithm
{
	std::vector<int*> cityIndex;
	int** cityDistanceMatrix;
	int* marks;
	int m_size;

public:
	GeneticAlgorithm(int** & distanceMatrix ,int genomSize, int populationSize);
	~GeneticAlgorithm();

	void generateGenoms(int size, int populationSize);
	void initArray(int* myArray, int size, int value);
	bool isDuplicateInArray(int* myArray, int size);

	void markPopulations();
	void tournamentSelection(int k)
	{

	}
};