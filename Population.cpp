#include "Population.h"
#include <iostream>
#include <iomanip>

using namespace std;

Population::Population()
{
}

Population::Population(const string& p, const int s) : size(s), protein(p)
{
	for (int i = 0; i < size; i++)
	{
		candidates.push_back(Folding(protein));
		nextGeneration.push_back(Folding(protein));
	}
}

Population::~Population()
{
}

void Population::evolve(){
	float totalFitness = 0.0, minFitness = 0.0, maxFitness = 0.0;
	vector<float> partsOfTotalFitness; // upper limits

	for (int folding = 0; folding < size; folding++){
		if (folding == 0 || candidates[folding].getFitness() < minFitness) minFitness = candidates[folding].getFitness();
		if (candidates[folding].getFitness() > maxFitness) maxFitness = candidates[folding].getFitness();
		totalFitness += candidates[folding].getFitness();
		partsOfTotalFitness.push_back( totalFitness );
	}
	cout << setprecision(5) << "Durchschnittliche Fitness: " << totalFitness / size << ", min: " << minFitness << ", max: " << maxFitness << endl;
	/*excel_avg << totalFitness / size << ";";
	excel_min << minFitness << ";";
	excel_max << maxFitness << ";";*/

	// select candidates for next generation (fitness proportional):
	for (int folding = 0; folding < size; folding++){
		float randomValue = float(rand() % (int)(totalFitness*100)) / 100;
		//cout << totalFitness << " - " << (totalFitness*1000) << " - " << randomValue << endl;
		for (int i = 0; i < size; i++){ // check which candidate got chosen:
			if (partsOfTotalFitness[i] >= randomValue){
				nextGeneration[folding] = Folding(candidates[i]);
				//cout << "candidate " << i << endl;
				break;
			}
		}
	}

	for (int i = 0; i < size; i++) candidates[i] = nextGeneration[i];

	// mutation:
	int nr_of_mutations = mutationRate * size / 100;
	for (int m = 0; m < nr_of_mutations; m++) candidates[ rand() % size ].mutate();

	// crossover:
	int nr_of_crossovers = crossoverRate * size / 100;
	for (int c = 0; c < nr_of_crossovers; c++) candidates[ rand() % size ].crossWith(candidates[rand() % size]);

	//cout << population[folding]->toString() << ", Anteil an Gesamtfitness: " << 100*population[folding]->getFitness()/totalFitness << endl;
}

void Population::showBestCandidate(){
	float best = -1.0, pos = 0;
	for (int c = 0; c < size; c++){
		float f = candidates[c].getFitness();
		if (f > best){
			best = f;
			pos = c;
		}
	}
	cout << "Bester Kandidat: " << endl << candidates[pos].toString() << endl;
}