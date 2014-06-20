#pragma once
#include "Folding.h"

class Population
{
private:
	const string protein = "10100110100101100101";
	const int size = 100;
	const int mutationRate = 2;	// in %
	const int crossoverRate = 20; // in %
	Folding bestCandidate;
	vector<Folding> candidates;
	vector<Folding> nextGeneration;

public:
	Population();
	Population(const string& protein, const int size);
	~Population();

	void evolve(const float pressure);
	void selectCandidatesForNextGeneration(const string& strategy, const float pressure);
	void showBestCandidate();
	Folding& getBestCandidate();
};

