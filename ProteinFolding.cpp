#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <stdlib.h>

#include "Population.h"
#include "Folding.h"

using namespace std;

int main() {
    //ofstream onepoint("none.txt");

    const string SEQ10 = "1001011100";
    const string SEQ20 = "10100110100101100101"; // max 9
    const string SEQ24 = "110010010010010010010011";
	const string SEQ25  = "1001010010100101001101111"; // max 12
	const string ABNAHME = "";
    const string SEQ25 = "0010011000011000011000011";
    const string SEQ36 = "000110011000001111111001100001100100";
    const string SEQ48 = "001001100110000011111111110000001100110010011111";
    const string SEQ50 = "11010101011110100010001000010001000101111010101011";

    int maxGenerations = 200;

    //for (int testingSeed = 0; testingSeed < 1; testingSeed++) {
        srand(time(NULL));
        //cout << "Seed " << testingSeed << "..." << endl;*/
        Population p(SEQ25, 1000);

        for (int generation = 1; generation <= maxGenerations; generation++) {
            cout << generation << ". Generation" << endl;
            p.evolve((float) generation / maxGenerations); // linear increase
        }

        cout << p.getBestCandidate().toString() << ";";
    //}

    //onepoint.close();

    return 0;
}