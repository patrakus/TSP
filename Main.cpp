#include <iostream>
#include "FileParser.h"
#include "GeneticAlgorithm.h"
#include <algorithm>
#include <vector>
#include <iterator>

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

	/*std::for_each(a->begin(), a->end(), 
		[](std::vector<int> vec) 
	{ 
		std::cout << vec.size() << std::endl;

		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		{
			std::cout << *it << " ";
		}

		std::cout << std::endl;
		system("pause");
	});*/

	/*
	std::cout << a[0][0] << std::endl;
	std::cout << a[1][0] << std::endl;
	std::cout << a[1][1] << std::endl;
	std::cout << a[2][0] << std::endl;
	std::cout << a[2][1] << std::endl;
	std::cout << a[2][2] << std::endl;
	*/

	GeneticAlgorithm<int> testA(a, parserTest.size, 5);
	testA.fitness();
	//testA.tournamentSelection(2);
	//testA.onePointCrossOver(0.5);

	system("pause");
	
	return 0;
}