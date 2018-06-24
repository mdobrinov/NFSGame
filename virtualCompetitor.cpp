#include "virtualCompetitor.h"
#include <iostream>
using namespace std;

VirtualCompetitor::VirtualCompetitor() :car(NULL) {
}
void VirtualCompetitor::setCar(Car* newCar) {
	car = newCar;
}
Car* VirtualCompetitor::getBestCar() const {
	return car;
}