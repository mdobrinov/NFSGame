#include "realCompetitor.h"
#include <iostream>
#include <cassert>
using namespace std;

RealCompetitor::RealCompetitor() : cash(0) {
}
void RealCompetitor::addCar(Car* car) {
	cars.push(car);
	if (bestCar != NULL) {
		if (car->getPower() > bestCar->getPower()) bestCar = car;
	}
	else {
		bestCar = car;
	}
}
Car* RealCompetitor::getBestCar() const {
	return bestCar;
}
void RealCompetitor::print() const {
	Competitor::print();
	cout << "	Cash: $" << cash << endl;
}
void RealCompetitor::setCash(double number) {
	cash = number;
}
double RealCompetitor::getCash() const {
	return cash;
}