#include <iostream>
#include <string>
#include <time.h>
#include <fstream>

#include "Population.h"
#include "Folding.h"

using namespace std;

int main(){
	srand(time(NULL));

	const string SEQ20 = "10100110100101100101";
	const string SEQ24 = "110010010010010010010011";
	const string SEQ25 = "0010011000011000011000011";
	const string SEQ36 = "000110011000001111111001100001100100";
	const string SEQ48 = "001001100110000011111111110000001100110010011111";
	const string SEQ50 = "11010101011110100010001000010001000101111010101011";

	Population p(SEQ20, 5000);

	for (int generation = 1; generation <= 100; generation++)
	{
		cout << generation << ". Generation" << endl;
		p.evolve();
	}

	p.showBestCandidate();

	system("pause");
	return 0;
}