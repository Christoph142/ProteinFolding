#include "Population.h"
#include <iostream>
#include <iomanip>
#include <fstream>

#include <stdlib.h>

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

	bestCandidate = candidates[0]; // just init with random candidate
}

Population::~Population()
{
}

void Population::evolve(const float pressure){
	//selection:
	selectCandidatesForNextGeneration( "fitnessproportional", pressure );

	// mutation:
	int nr_of_mutations = mutationRate * size / 100;
	for (int m = 0; m < nr_of_mutations; m++) candidates[ rand() % size ].mutate();

	// crossover:
	int nr_of_crossovers = crossoverRate * size / 100;
	for (int c = 0; c < nr_of_crossovers; c++) candidates[ rand() % size ].crossWith(candidates[rand() % size]);
}

void Population::showBestCandidate(){
	bestCandidate.toString();
}

Folding& Population::getBestCandidate(){
	return bestCandidate;
}

void Population::selectCandidatesForNextGeneration( const string& strategy, const float pressure ){

	if (strategy == "fitnessproportional") // fitness proportional:
	{
		float totalFitness = 0.0, minFitness = 0.0, maxFitness = 0.0;
		vector<float> partsOfTotalFitness; // upper limits
                
        int bestPos = 0;

		for (int folding = 0; folding < size; folding++){
			if (folding == 0 || candidates[folding].getFitness() < minFitness) minFitness = candidates[folding].getFitness();
			if (candidates[folding].getFitness() > maxFitness) {
				maxFitness = candidates[folding].getFitness();
				bestPos = folding;
            }
			totalFitness += candidates[folding].getFitness();
			partsOfTotalFitness.push_back(totalFitness);
		}
		if(candidates[bestPos].getFitness() > bestCandidate.getFitness()) bestCandidate = candidates[bestPos]; // remember best all-time candidate
		ofstream file("test.txt", ios::app);
		file << totalFitness << ";";
		cout << setprecision(5) << "Durchschnittliche Fitness: " << totalFitness / size << ", min: " << minFitness << ", max: " << maxFitness << endl;
		/*excel_avg << totalFitness / size << ";";
		excel_min << minFitness << ";";
		excel_max << maxFitness << ";";*/
                
                

		for (int folding = 0; folding < size; folding++){
			float randomValue = float(rand() % (int)(totalFitness * 100)) / 100;
			//cout << totalFitness << " - " << (totalFitness*1000) << " - " << randomValue << endl;
			for (int i = 0; i < size; i++){ // check which candidate got chosen:
				if (partsOfTotalFitness[i] >= randomValue){
					nextGeneration[folding] = Folding(candidates[i]);
					//cout << "candidate " << i << endl;
					break;
				}
			}
		}
	}
	else // tournier:
	{
		
		const int nr_of_opponents = (20 * pressure) + 1;
		
		int champ = 0;
		float fitnessOfChamp = 0.0;

		for (int folding = 0; folding < size; folding++)
		{
			int winner = 0;
			float fitnessOfWinner = 0;

			for (int o = 0; o < nr_of_opponents; o++) // determine winner:
			{
				int randomOpponent = rand() % size;
				if (candidates[randomOpponent].getFitness() >= fitnessOfWinner){
					fitnessOfWinner = candidates[randomOpponent].getFitness();
					winner = randomOpponent;
				}
			}

			nextGeneration[folding] = Folding( candidates[winner] );

			if (fitnessOfWinner >= fitnessOfChamp){
				champ = winner;
				fitnessOfChamp = fitnessOfWinner;
			}

			if (fitnessOfChamp > bestCandidate.getFitness()) bestCandidate = candidates[champ];
		}

		//cout << "Champ: " << fitnessOfChamp << endl;
	}

	for (int i = 0; i < size; i++) candidates[i] = nextGeneration[i];
}