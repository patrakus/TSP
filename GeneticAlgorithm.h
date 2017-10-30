#pragma once
#include <vector>

class GeneticAlgorithm
{
	std::vector<int*> cityIndex;
	int** cityDistanceMatrix;



public:
	GeneticAlgorithm(int** & distanceMatrix ,int genomSize);
	~GeneticAlgorithm();

	void generateGenoms(int size);
	void initArray(int* myArray, int size, int value);
	bool isDuplicateInArray(int* myArray, int size);


};

