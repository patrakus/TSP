#pragma once
#include <vector>
#include "DNA.h"
#include <forward_list>
#include <random>
#include <iterator>
#include <memory>
#include <iostream>

template<typename type>
class GeneticAlgorithm
{
	std::vector<DNA<type>> DNAForwardList;
	//std::vector<DNA<type>> bestSelection; // czy w takiej formiejest skonstruowany?
	std::vector<DNA<type>> newGeneration;

	std::mt19937 randomEngine;
	std::uniform_int_distribution<int>* distribution;
	//std::vector<int*> cityIndex;
	//std::vector<int*> newCityIndex;
	std::shared_ptr<std::vector<std::vector<int>>> cityDistanceMatrix;
	//int* marks;
	DNA<type> theBestIndividual;
	

public:
	GeneticAlgorithm(std::shared_ptr<std::vector<std::vector<int>>> distanceMatrix, int genomSize, int populationSize, unsigned int rd);
	~GeneticAlgorithm();

	void generatePopulation(size_t size, size_t populationSize);
	//void initArray(int* myArray, int size, int value);
	//bool isDuplicateInArray(int* myArray, int size);

	void fitness();

	void doWork();

	int tournamentSelection(int k);

	void onePointCrossOver(float probalityOfMixing, int parent[]);

	void inverseMutation(float probalityOfMutation, size_t childIndex);

private:
	void swap(int parentA, int parentB, int crossPoint);
	inline int distance(int p1, int p2) { return p2 - p1; }
	bool isDuplicate(DNA<type> gen);

	void writeTheBestIndividual()
	{
		std::cout << "The shortest way have: " << theBestIndividual.mark << "km" << std::endl;
	}

	void findTheBest()
	{
		size_t theBest = 0;

		for (size_t i = 1; i < DNAForwardList.size(); i++)
		{
			if (DNAForwardList[theBest].mark > DNAForwardList[i].mark)
			{
				theBest = i;
			}
		}

		if (theBestIndividual.mark > 0)
		{
			if (theBestIndividual.mark > DNAForwardList[theBest].mark)
			{
				theBestIndividual = DNAForwardList[theBest];

				writeTheBestIndividual();
			}
		}
		else
		{
			theBestIndividual = DNAForwardList[theBest];

			writeTheBestIndividual();
		}
	}

	void resetFitness()
	{
		for (size_t i = 0; i < DNAForwardList.size(); i++)
		{
			DNAForwardList[i].mark = 0;
		}
	}
};

template<typename type>
GeneticAlgorithm<type>::GeneticAlgorithm(std::shared_ptr<std::vector<std::vector<int>>> distanceMatrix, int genomSize, int populationSize, unsigned int rd) :
	cityDistanceMatrix(distanceMatrix), randomEngine(rd) /*randomEngine(128468406)/*, distribution(0, cityDistanceMatrix->size() - 1)*/ //this will casue execption in vector, but why?
{
	distribution = new std::uniform_int_distribution<int>(0, cityDistanceMatrix->size() - 1);

	theBestIndividual.mark = -1;

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
	// todo: stworzenie genomu bez duplikatów

	for ( size_t i = 1; i < populationSize; i++)
	{
		DNA<type> gene;

		for (size_t j = 0; j < size; j++)
		{
			gene.genom.push_back(distribution->operator()(randomEngine));

			while (isDuplicate(gene))
			{
				gene.genom[j] = distribution->operator()(randomEngine);
			}
			
		}

		/*for (size_t j = 0; j < size; j++)
		{
			std::cout << gene.genom[j] << " ";
		}*/

		//std::cout << std::endl;
		//system("pause");


		DNAForwardList.push_back(gene);
	}
}

template<typename type>
void GeneticAlgorithm<type>::fitness()
{
	

	for (size_t i = 0; i < DNAForwardList.size(); i++)
	{
		for (size_t j = 0; j < DNAForwardList[i].genom.size(); j++)
		{
			if (j + 1 < DNAForwardList[i].genom.size() )
			{

				int firstCity = DNAForwardList[i].genom[j];
				int secondCity = DNAForwardList[i].genom[j + 1];

				if (firstCity < secondCity) // macierz odleg³oœci nie jest lustrzana wiêc trzeba podmieniæ kolejnoœæ wartoœci
				{
					int tmp = firstCity;
					firstCity = secondCity;
					secondCity = tmp;
				}

				DNAForwardList[i].mark += cityDistanceMatrix->at(firstCity).at(secondCity);
			}
			else
			{
				int firstCity = DNAForwardList[i].genom[j];
				int secondCity = DNAForwardList[i].genom[0];

				if (firstCity < secondCity) // macierz odleg³oœci nie jest lustrzana wiêc trzeba podmieniæ kolejnoœæ wartoœci
				{
					int tmp = firstCity;
					firstCity = secondCity;
					secondCity = tmp;
				}

				DNAForwardList[i].mark += cityDistanceMatrix->at(firstCity).at(secondCity);
			}
		}
		//std::cout << "Fitness: " << DNAForwardList[i].mark << std::endl;
	}
}

template<typename type>
void GeneticAlgorithm<type>::doWork()
{
	//std::cout << DNAForwardList.size() << std::endl;

	resetFitness();

	fitness();

	findTheBest();

	for (size_t i = 0; i < DNAForwardList.size(); i+=2)
	{
		int parent[2];

		for (int i = 0; i < 2; i++)
		{
			parent[i] = tournamentSelection(10);
		}

		onePointCrossOver(0.80f, parent);
	}

	for (size_t i = 0; i < newGeneration.size(); i++)
	{
		inverseMutation(0.05f, i);
	}

	DNAForwardList = newGeneration;
	newGeneration.clear();
}

template<typename type>
int GeneticAlgorithm<type>::tournamentSelection(int k) // k - iloœc zwyciêsców np top 3 najlepszych zawodników
{
	unsigned int *selectedIndividuals = new unsigned int[k];

	std::uniform_int_distribution<> smallDist(0, DNAForwardList.size() - 1);

	for (size_t j = 0; j < k; j++)
	{
		//std::cout << smallDist(randomEngine);

		selectedIndividuals[j] = smallDist(randomEngine);
		//std::cout << "Wartoœæ: " << DNAForwardList[selectedIndividuals[j]].mark << std::endl;
	}

	int betterIndividual = selectedIndividuals[0];

	for (size_t j = 1; j < k; j++)
	{
		if (DNAForwardList[betterIndividual].mark > DNAForwardList[selectedIndividuals[j]].mark)
		{
			betterIndividual = selectedIndividuals[j];
		}
	}

	delete selectedIndividuals;

	//std::cout <<"\n" << "Wartoœæ: " << DNAForwardList[betterIndividual].mark << std::endl;

	return betterIndividual;
}

template<typename type>
void GeneticAlgorithm<type>::onePointCrossOver(float probalityOfMixing, int parent[])
{
	// powinno siê wylosowaæ 2 rodziców
	std::uniform_real_distribution<float> floatDist(0.f, 1.f);
	std::uniform_int_distribution<int> intDist(0, DNAForwardList[0].genom.size() - 1);
	std::uniform_int_distribution<> smallDist(0, DNAForwardList.size() - 1);

	float probability = floatDist(randomEngine);

	if (probability < probalityOfMixing)
	{
		int crossPoint = intDist(randomEngine);
		swap(parent[0], parent[1], crossPoint);
	}
	else
	{
		newGeneration.push_back(DNAForwardList[parent[0]]);
		newGeneration.push_back(DNAForwardList[parent[1]]);
	}

}
template<typename type>
void GeneticAlgorithm<type>::swap(int parentA, int parentB, int crossPoint)
{
	DNA<type> child1 = DNAForwardList[parentA];
	DNA<type> child2 = DNAForwardList[parentB];

	//std::cout << "Gen1: ";
	//for (size_t j = 0; j < child1.genom.size(); j++)
	//{
	//	std::cout << child1.genom[j] << " ";
	//}
	//std::cout << std::endl;
	//std::cout << "Gen2: ";
	//for (size_t j = 0; j < child1.genom.size(); j++)
	//{
	//	std::cout << child2.genom[j] << " ";
	//}

	//for (size_t i = child1.genom.size() - 1; i >= crossPoint + 1; i--)
	//{
	//	child1.genom[i] = DNAForwardList[parentB].genom[i];
	//	child2.genom[i] = DNAForwardList[parentA].genom[i];
	//}

	

	int temp;

	for (size_t i = 0; i < child1.genom.size(); i++)
	{
		if (i > crossPoint) break;

		temp = DNAForwardList[parentA].genom[i];
		int incrementer = -1;

		for (size_t j = 0; j < child1.genom.size(); j++)
		{
			if (temp == child1.genom[j] && i != j)
			{
				incrementer++;
				j = 0;

				if (!(i + incrementer < child1.genom.size()))
				{
					incrementer = -i;
				}

				temp = DNAForwardList[parentB].genom[i + incrementer];
			}
		}

		child1.genom[i] = temp;
	}

	for (size_t i = 0; i < child1.genom.size(); i++)
	{
		if (i > crossPoint) break;

		temp = DNAForwardList[parentB].genom[i];
		int incrementer = -1;

		for (size_t j = 0; j < child1.genom.size(); j++)
		{
			if (temp == child2.genom[j] && i != j)
			{
				incrementer++;
				j = 0;

				if (!(i + incrementer < child2.genom.size()))
				{
					incrementer = -i;
				}

				temp = DNAForwardList[parentA].genom[i + incrementer];
			}
		}

		child2.genom[i] = temp;
	}

	/*std::cout << "Gen1: ";
	for (size_t j = 0; j < child1.genom.size(); j++)
	{
		std::cout << child1.genom[j] << " ";
		system("pause");
	}
	std::cout << std::endl;
	std::cout << "Gen2: ";
	for (size_t j = 0; j < child1.genom.size(); j++)
	{
		std::cout << child2.genom[j] << " ";
		system("pause");
	}
	std::cout << std::endl;*/

	newGeneration.push_back(child1);
	newGeneration.push_back(child2);
}

template<typename type>
void GeneticAlgorithm<type>::inverseMutation(float probalityOfMutation, size_t childIndex)
{
	std::uniform_int_distribution<int> intDist(0, DNAForwardList[0].genom.size() - 1);
	std::uniform_real_distribution<float> floatDist(0.f, 1.f);

	if (floatDist(randomEngine) < probalityOfMutation)
	{
		unsigned int point1, point2;

		point1 = intDist(randomEngine);
		point2 = intDist(randomEngine);
		int tmp;

		if (point2 < point1)
		{
			tmp = point1;
			point1 = point2;
			point2 = tmp;
		}

		/*for (size_t i = 0; i < newGeneration[childIndex].genom.size(); i++)
		{
			std::cout << newGeneration[childIndex].genom[i] << ":";
		}
		std::cout << std::endl;*/

		for (size_t i = point1, j = point2;  !(i >= j) ; i++, j--)
		{
			//std::cout << distance(i, j) << std::endl;
			/*std::cout << i << std::endl;
			std::cout << j << std::endl;
			std::cout << "-------------------------" << std::endl;*/

			tmp = newGeneration[childIndex].genom[i];
			newGeneration[childIndex].genom[i] = newGeneration[childIndex].genom[j];
			newGeneration[childIndex].genom[j] = tmp;
		}

		/*for (size_t i = 0; i < newGeneration[childIndex].genom.size(); i++)
		{
			std::cout << newGeneration[childIndex].genom[i] << ":";
		}
		std::cout << std::endl;*/
		//system("pause");
	}
}

template<typename type>
bool GeneticAlgorithm<type>::isDuplicate(DNA<type> gen)
{

	for (size_t i = 0; i < gen.genom.size(); i++)
	{
		for (size_t j = 1; j < gen.genom.size(); j++)
		{
			if (gen.genom[i] == gen.genom[j] && i != j)
			{
				return true;
			}
		}
	}
	return false;
}