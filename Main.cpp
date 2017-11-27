#include <iostream>
#include "FileParser.h"
#include "GeneticAlgorithm.h"
#include <algorithm>
#include <vector>
#include <iterator>
#include <chrono>

// turniejowa selekcja
// ko³a ruletki selekcja

// do przeczytania

/*
program ma wczytywac dowolny plik

populacja m na n

selekcja ruletka i turniej
krzyzowanie(dowolna) min.1 --> z wyk³adów
mutacja(dowolna) min.1 --. z wyk³adów

zapetliæ aby wykonaæ milion pokoleñ

algorytm ma znaleœæ najlepszego osobnika ze wszyskich pokoleñ

8 stycznia s¹ zawody
*/

int main()
{
	std::cout << "Hello TSP" << std::endl;

	FileParser parserTest;

	auto a = parserTest.loadFile("berlin52.txt");

	std::shared_ptr<std::vector<std::vector<int>>> b(a);

	unsigned int rd = std::random_device()();

	auto start = std::chrono::high_resolution_clock::now();

	GeneticAlgorithm<int> testA(a, parserTest.size, 20, rd);

	for (size_t i = 0; i < 500000; i++)
	{
		testA.doWork();
	}


	

	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << std::endl;

	//testA.fitness();
	//testA.tournamentSelection(3);
	//testA.onePointCrossOver(0.75);

	system("pause");
	
	return 0;
}