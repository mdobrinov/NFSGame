#include <iostream>
#include "competitor.h"
using namespace std;

Competitor::Competitor() :competitorId(0), skills(0) {
}
Competitor::~Competitor() {
}
void Competitor::setId(int number) {
	competitorId = number;
}
void Competitor::setSkills(int newSkills) {
	skills = newSkills;
}
int Competitor::getSkills() const {
	return skills;
}
int Competitor::getCompetitorId() const {
	return competitorId;
}
void Competitor::print() const {
	cout << "> ID: " << competitorId << "		Skills: " << skills;
	cout << "	Best Car power: " << getBestCar()->getPower();
}
