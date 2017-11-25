#pragma once
#include <vector>
#include "DNA.h"
#include <forward_list>
#include <random>
#include <iterator>
#include <memory>

template<typename type>
class GeneticAlgorithm
{
	std::forward_list<DNA<type>> DNAForwardList;

	std::mt19937 randomEngine;
	std::uniform_int_distribution<int>* distribution;
	//std::vector<int*> cityIndex;
	std::vector<int*> newCityIndex;
	std::shared_ptr<std::vector<std::vector<int>>> cityDistanceMatrix;
	//int* marks;
	int m_size;
	

public:
	GeneticAlgorithm(std::shared_ptr<std::vector<std::vector<int>>> distanceMatrix, int genomSize, int populationSize);
	~GeneticAlgorithm();

	void generatePopulation(size_t size, size_t populationSize);
	//void initArray(int* myArray, int size, int value);
	bool isDuplicateInArray(int* myArray, int size);

	void fitness();
	void tournamentSelection(int k);

	void onePointCrossOver(float probalityOfMixing);

private:
	void swap(int* a, int* b, int crossPoint);
};

template<typename type>
GeneticAlgorithm<type>::GeneticAlgorithm(std::shared_ptr<std::vector<std::vector<int>>> distanceMatrix, int genomSize, int populationSize) :
	cityDistanceMatrix(distanceMatrix), randomEngine(128468406)/*, distribution(0, cityDistanceMatrix->size() - 1)*/ //this will casue execption in vector, but why?
{
	distribution = new std::uniform_int_distribution<int>(0, cityDistanceMatrix->size() - 1);

	generatePopulation(genomSize, populationSize);
}

template<typename type>
GeneticAlgorithm<type>::~GeneticAlgorithm()
{
	delete distribution;
}


/*
	Generuje populacje o rozmiarze size
*/
template<typename type>
void GeneticAlgorithm<type>::generatePopulation(size_t size, size_t populationSize)
{
	for ( size_t i = 0; i < populationSize; i++)
	{
		 DNA<type> gene;

		for (size_t i = 0; i < size; i++)
		{

			gene.genom.push_front(distribution->operator()(randomEngine));
		}

		DNAForwardList.push_front(gene);
	}
}

template<typename type>
void GeneticAlgorithm<type>::fitness()
{
	for (std::forward_list<DNA<type>>::iterator it = DNAForwardList.begin(); it != DNAForwardList.end(); it++)
	{
		for (std::forward_list<type>::iterator git = it->genom.begin(); git != it->genom.end(); git++)
		{
			if (git + 1 != it->genom.end())
			{
				it->mark += *git + *(git + 1);
			}
			else
			{
				it->mark += *git + it->genom.firs()
			}
		}
	}
}