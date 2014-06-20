#include <string>
#include <vector>

#pragma once

using namespace std;

class Folding
{
private:
	string protein;
	vector<int> directions;
	float fitness = -1.0;

public:
	Folding();
	Folding(const string& protein);
	~Folding();

	Folding(const Folding& f);

	const float getFitness();
	void checkFitness();
	void mutate();
	void crossWith(Folding& f);
	string toString();

	void operator=(const Folding& f);
};