#include "Folding.h"

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

// Test Tobi

Folding::Folding()
{
}

Folding::Folding(const string& prot) : protein(prot){
																					 // 1st element = no direction
	directions.push_back(rand() % 2);												 // 2nd element right / left = mirrored
	for (int i = 2; i < protein.length() - 1; i++) directions.push_back(rand() % 3); // all other elements: left, straight, right
}


Folding::~Folding()
{
}

Folding::Folding(const Folding& orig) : protein(orig.protein), directions(orig.directions), fitness(orig.fitness){}

const float Folding::getFitness(){
	if (fitness < 0) checkFitness();
	return fitness;
}
void Folding::checkFitness(){
	const int size = 100;// protein.size() + 1;
	int positions[size][size];

	int x, y;
	x = y = size / 2;

	int hydrophobicContacts = 1, overlaps = 1;

	positions[x][y] = (protein.at(0) == '0' ? 0 : 1);
	int direction = 0; // up
	y--;
	positions[x][y] = (protein.at(1) == '0' ? 0 : 1);

	for (int i = 0; i < directions.size(); i++){

		// get direction:
		if		(directions.at(i) == 0) direction = (direction-1)%4; // left turn
		else if (directions.at(i) == 2) direction = (direction+1)%4; // right turn

		// get position:
		if		(direction == 0) y--; // up
		else if (direction == 1) x++; // right
		else if (direction == 2) y++; // down
		else if (direction == 3) x--; // left

		if (positions[x][y] >= 0){ overlaps++; continue; } // overlapping
		positions[x][y] = ( protein.at(i+2) == '0' ? 0 : 1 );

		if (protein.at(i + 2) == '1'){ // hydrophob -> check for neighbours:
			if (positions[x][y + 1] == 1 && direction != 0) hydrophobicContacts++;
			if (positions[x - 1][y] == 1 && direction != 1) hydrophobicContacts++;
			if (positions[x][y - 1] == 1 && direction != 2) hydrophobicContacts++;
			if (positions[x + 1][y] == 1 && direction != 3) hydrophobicContacts++;
		}
	}
	
	fitness = float(hydrophobicContacts) / float(overlaps);
	//cout << "Fitness: " << fitness << endl;
}

string Folding::toString(){
	ostringstream o;

	o << "directions: ";
	for (int i = 0; i < directions.size(); i++) o << directions[i];
	o << ", fitness: " << setprecision(5) << getFitness();
	
	// visualize:
	const int size = 50;// protein.size() + 1;
	char positions[size][size];
	int x, y;
	x = y = size / 2;

	positions[x][y] = (protein.at(0));
	int direction = 0; // up
	y--;
	positions[x][y] = (protein.at(1));
	
	o << ", evaluated directions: u";
	for (int i = 0; i < directions.size(); i++){

		// get direction:
		if		(directions.at(i) == 0) direction = (direction-1) % 4; // left turn
		else if (directions.at(i) == 2) direction = (direction+1) % 4; // right turn
		
		// get position:
		if		(direction == 0){ y--; o << "u"; } // up
		else if (direction == 1){ x++; o << "r"; } // right
		else if (direction == 2){ y++; o << "d"; } // down
		else if (direction == 3){ x--; o << "l"; } // left

		if (positions[x][y] >= 0) positions[x][y] = 'X'; // overlapping
		else positions[x][y] = protein.at(i + 2);
	}

	o << endl;
	for (int i = 0; i < 50; i++){
		for (int j = 0; j < 50; j++){
			o << positions[j][i];
		}
		o << endl;
	}

	return o.str();
}

void Folding::mutate(){
	directions.at( rand() % directions.size() ) = rand() % 3;
	fitness = -1.0; // fitness has to be recalculated on next usage
}

void Folding::crossWith(Folding& partner){

	string strategy = "onepoint";

	if (strategy == "onepoint"){
		int crossoverPoint = rand() % directions.size();
		//cout << "Crossing " << this->toString() << " with " << partner.toString() << " at " << crossoverPoint << endl;
		for (int p = 0; p < crossoverPoint; p++)
		{
			int helper = directions.at(p);
			directions.at(p) = partner.directions.at(p);
			partner.directions.at(p) = helper;
		}
		fitness = -1.0; // fitness has to be recalculated on next usage
	}
	else{ // uniform:
		float bias = 0.5;// rand() % 100 / 100;

		for (int p = 0; p < directions.size(); p++){
			if (rand() % 100 > bias * 100) continue;

			int helper = directions.at(p);
			directions.at(p) = partner.directions.at(p);
			partner.directions.at(p) = helper;
		}
	}
}

void Folding::operator=(const Folding& f){
	protein = f.protein;
	directions = f.directions;
	fitness = f.fitness;
}