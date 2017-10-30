#include <iostream>
#include "FileParser.h"
#include "GeneticAlgorithm.h"

// turniejowa selekcja
// ko³a ruletki selekcja

int main()
{
	std::cout << "Hello TSP" << std::endl;

	FileParser parserTest;

	int** a = parserTest.loadFile("berlin52.txt");
	/*
	std::cout << a[0][0] << std::endl;
	std::cout << a[1][0] << std::endl;
	std::cout << a[1][1] << std::endl;
	std::cout << a[2][0] << std::endl;
	std::cout << a[2][1] << std::endl;
	std::cout << a[2][2] << std::endl;
	*/

	GeneticAlgorithm testA(a, parserTest.size, 25);
	testA.markPopulations();

	system("pause");
	
	return 0;
}