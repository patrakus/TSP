#include <iostream>
#include "FileParser.h"
#include "GeneticAlgorithm.h"

// turniejowa selekcja
// ko�a ruletki selekcja

// do przeczytania

/*
program ma wczytywac dowolny plik

populacja m na n

selekcja ruletka i turniej
krzyzowanie(dowolna) min.1 --> z wyk�ad�w
mutacja(dowolna) min.1 --. z wyk�ad�w

zapetli� aby wykona� milion pokole�

algorytm ma znale�� najlepszego osobnika ze wszyskich pokole�

8 stycznia s� zawody
*/

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
	testA.tournamentSelection(10);

	system("pause");
	
	return 0;
}