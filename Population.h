#pragma once
#include "Folding.h"

class Population
{
private:
	const string protein = "10100110100101100101";
	const int size = 100;
	const int mutationRate = 2;	// in %
	const int crossoverRate = 20; // in %
	vector<Folding> candidates;
	vector<Folding> nextGeneration;

public:
	Population();
	Population(const string& protein, const int size);
	~Population();

	void selectCandidatesForNextGeneration(const string& strategy);
	void evolve();
	void showBestCandidate();
};

